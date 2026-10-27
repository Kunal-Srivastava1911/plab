# PLAB technical specification

Version 1, 2026-10-27. Source document: the "PLAB: Predictive Lexical Analysis Buffering" research proposal. This spec is the implementation contract; section numbers are referenced from `DESIGN_NOTES.md`.

## 1. Goal and hypotheses

Make lexing cost scale with *phrases* instead of *bytes*. Real code is repetitive at the token level, so the last two tokens often determine the next few tokens byte for byte. PLAB stores those continuations, checks them against the source with one SIMD compare, and commits all matching tokens at once.

| ID | Hypothesis | Target |
| --- | --- | --- |
| H1 Coverage | Fraction of tokens committed through prediction, with at most 512 KB static plus 32 KB dynamic predictor state | At least 50%, with 3 or more tokens per accepted phrase |
| H2 Speed | Throughput of PLAB over a baseline vs the baseline alone | At least 1.5x over re2c; at least 1.2x over a SIMD tokenizer (stretch) |
| H3 Mechanism | Branch mispredicts per token and instructions per byte | Mispredicts down 40% or more, instructions per byte down 2x or more, cache misses not up |
| H4 Robustness | Slowdown on adversarial inputs | At most 5% |
| H5 Exactness | Token stream equality with the baseline | Always |

Scope of version 1: the C language (core), plus Python in the Phase 0 limit study only.

## 2. Architecture overview

```
            +============================================================+
 source ==> | PLAB front stage                                           |
 (padded)   |                                                            |
            |  ctx = hash(id(tok[-2]), id(tok[-1]), sigma)               |
            |        |                                                   |
            |        v                                                   |
            |  [copy predictor]  [static order-2]  [static order-1]      |
            |        \________ longest match with conf >= 2 ________/    |
            |                          |                                 |
            |                          v                                 |
            |             phrase record (128 B)                          |
            |                          |                                 |
            |   32-byte SIMD compare + guard check + sigma check         |
            |          |                               |                 |
            |    accept b > 0                     accept = 0             |
            |          v                               v                 |
            |   commit up to 8 tokens         baseline_lex_one()         |
            |   (vector stores)               (re2c or flex, unchanged)  |
            +==========|===============================|=================+
                       v                               v
                   SoA token buffer: kind[], start[], len[], id[], sigma[]
```

`id(tok)` is the intern ID for identifiers and the token kind for everything else.

## 3. Exactness rule (must be implemented exactly)

Definitions:

- `k`: maximum lookahead of the token spec, the longest run of bytes the lexer may read past a token's last byte before deciding the token has ended.
- `sigma`: the lexer state signature (section 4), compared with equality only.
- A phrase record holds `L` bytes recorded starting at a token end, the token boundaries inside them, the `sigma` it was recorded in (`sigma_in`) and the state after it (`sigma_out`).

**Lemma.** At position `p` with state `sigma == rec.sigma_in`, if `src[p, p + L)` equals `rec.bytes[0, L)` and the guard condition holds for the bytes after the last committed token, the baseline lexer would emit exactly the recorded tokens.

**Guard condition.** For a committed token ending at offset `b` with kind `t`, the byte `src[p + b]` must not be in `EXTENDS[t]`, a 256-bit set of bytes that could extend a token of kind `t`. `EXTENDS` may over-approximate (that only lowers coverage) but must never under-approximate (that breaks correctness). Token kinds whose end decision needs more than one byte of lookahead are marked `GUARD_EXACT` and require the next `k_t` bytes to match recorded guard bytes, or are simply never the last committed token.

**Partial acceptance.** Let `a` be the offset of the first mismatching byte (32 if none within `L`). Commit the longest prefix of tokens whose end `b` satisfies `b < a` and whose guard byte `src[p + b]` is not in `EXTENDS[t]`. Because `src[p + b]` lies inside the matched region or is checked explicitly, the rule is exact.

**Version 1 EXTENDS sets for C (conservative):**

| Token kind | EXTENDS (bytes that make the token unsafe to end here) |
| --- | --- |
| identifier, keyword | `[A-Za-z0-9_$]`, plus `\` (UCNs) and bytes >= 0x80 |
| number (pp-number) | `[A-Za-z0-9_.]`, `'` (C23 digit separator), `+` and `-` (after e, E, p, P: just always include them) |
| string, char literal | none (the closing quote ends it) |
| `<` | `<`, `=`, `:`, `%` (digraphs) |
| `<<` | `=` |
| `>` | `>`, `=` |
| `>>` | `=` |
| `-` | `-`, `=`, `>` |
| `+` | `+`, `=` |
| `&` `\|` | the same char, `=` |
| `*` `^` `!` `=` | `=` |
| `%` | `=`, `>`, `:` |
| `/` | `=`, `*`, `/` (comment starts) |
| `.` | `0-9`, `.` (`...` needs 2 bytes: mark `.` followed by `.` as unsafe) |
| `#` | `#` |
| `:` | `>` (digraph) |
| other punctuators | none |

Phrases include the whitespace and comments between tokens, because whitespace is part of the verified bytes.

## 4. Lexer state signature sigma (C, 16 bits)

| Bit(s) | Meaning |
| --- | --- |
| 0 | `at_line_start`: only whitespace since the last newline (decides whether `#` starts a directive) |
| 1 | `in_directive`: inside a preprocessor line |
| 2 | `include_mode`: after `#include` / `#include_next`, where `<...>` is a header-name |
| 3 to 15 | reserved, zero |

Rules: a record stores `sigma_in` and `sigma_out`. Committing a phrase sets `sigma = sigma_out`. The miner never records phrases that contain a line-continuation backslash, a raw-string or header-name token, or that cross the newline ending a directive with tokens on both sides.

## 5. Data structures

### 5.1 Phrase record

```c
typedef struct plab_rec {          // 128 bytes, 64-byte aligned
    uint16_t tag;                  // partial tag of the full context
    uint16_t sigma_in;
    uint8_t  len;                  // L, 1..32 bytes
    uint8_t  ntok;                 // 1..8
    uint8_t  conf;                 // 2-bit saturating counter in the low bits
    uint8_t  newlines;             // newline count inside bytes[0, len)
    uint8_t  bytes[32];
    uint32_t ends;                 // bit i set if a token ends at offset i + 1
    uint16_t desc[8];              // (end_offset << 10) | kind, end_offset 1..32
    uint32_t intern[8];            // intern IDs for identifier tokens, else 0
    uint32_t epoch;                // intern IDs valid only if epoch == interner epoch
    uint32_t next_ctx;             // context hash after the full phrase
    uint16_t sigma_out;
    uint8_t  source;               // 0 static order-1, 1 static order-2, 2 copy
    uint8_t  pad[25];
} plab_rec;
_Static_assert(sizeof(plab_rec) == 128, "record must be 128 bytes");
```

### 5.2 Predictors

- **Copy predictor** (dynamic, per file): 4096 entries of `{uint16_t tag; uint8_t conf; uint32_t tok_index;}` indexed by the low 12 bits of the order-2 context hash. The draft is materialized from the token buffer: bytes from the end of token `tok_index` to the end of up to 8 following tokens, capped at 32 bytes. Requires `sigma[]` in the token buffer.
- **Static tables** (offline, per language): order-2 table of 2048 records and order-1 table of 2048 records (2 x 256 KB). Built by `plab_build_table` from the training corpus. Loaded from a `.plabt` binary file (header: magic `PLAB`, version, language, k, record counts, then records).
- **Selection order:** copy (if tag hits and conf >= 2), then static order-2, then static order-1, otherwise fallback with no probe.
- **Context hash:** `h = mix64(id[-2] * P1 ^ id[-1] * P2 ^ sigma)`; index from the low bits, tag from bits 48 to 63. Use a fixed `mix64` (splitmix64 finalizer).

### 5.3 Token buffer (SoA)

```c
typedef struct plab_tokens {
    uint8_t  *kind;
    uint32_t *start;     // byte offset in source
    uint32_t *len;
    uint32_t *id;        // intern ID or literal index
    uint16_t *sigma;     // state before this token
    uint32_t  count, capacity;
    uint32_t  lines;     // newline count so far
} plab_tokens;
```

Capacity is preallocated as `source_len / 2 + 64` so commits never branch on capacity.

### 5.4 Interner

Open-addressing hash table keyed by spelling, append-only during one run, with an `epoch` incremented per run. Static-table records carry spellings via their `bytes`; their `intern` IDs are filled lazily on first commit in a run and stamped with the current epoch.

## 6. Hot loop and governor

```c
while (p < end) {
    plab_rec *r = plab_probe(ctx, sigma);               // NULL if no confident match
    if (r) {
        PLAB_PREFETCH(plab_slot_for(r->next_ctx));
        uint32_t eq  = cmpeq32_mask(src + p, r->bytes); // AVX2 or scalar twin
        uint32_t a   = eq == 0xFFFFFFFFu ? 32 : tzcnt32(~eq);
        uint32_t b   = plab_accept_len(r, src + p, a);  // section 3, branch-free
        if (b) { plab_commit(&toks, r, p, b); p += b; ctx = plab_ctx_after(r, b); sigma = plab_sigma_after(r, b); plab_train_hit(r, b); continue; }
        plab_train_miss(r);
    }
    plab_baseline_lex_one(src, &p, &sigma, &toks);       // unchanged baseline
    ctx = plab_ctx_push(ctx, &toks);
    plab_train_enqueue(ctx, &toks);
}
```

- `plab_accept_len`: mask `ends` to bits below `a`, then walk back from the highest set bit at most 8 steps applying the guard test; return the offset of the last safe end, or 0.
- Training writes go to a 64-entry ring and are applied every 64 tokens.
- **Governor:** input split into 4 KB windows. A window runs the speculative loop if the last speculative window's gain estimate `committed_tokens * C_ref - probes * C_p - failed_probes * P_br` was positive; otherwise it runs a plain baseline loop (separately compiled, no PLAB branches). When off, every 64th window runs speculatively as a sample. Counters are per window.

## 7. Cost model and break-even

```
F    = C_ctx + g * (C_p + P_br)
S(a) = C_ref / (a * C_hit / n + (1 - a) * (C_ref + F))
a*   = F / (C_ref + F - C_hit / n)
```

`a` is token coverage, `g` the fraction of fallback tokens that issued a failed probe. Assumed values to be replaced by measurements: C_hit = 10 cycles per phrase, n = 4, C_ctx = 1, C_p = 6, P_br = 17.

| Baseline (C_ref cycles/token) | g | Break-even a* | S at 0.5 | S at 0.7 | S at 0.9 |
| --- | --- | --- | --- | --- | --- |
| SIMD tokenizer (8) | 0.1 | 0.38 | 1.16 | 1.56 | 2.37 |
| Direct-coded, re2c (15) | 0.1 | 0.21 | 1.44 | 2.07 | 3.68 |
| Table-driven, flex (30) | 0.1 | 0.11 | 1.68 | 2.56 | 5.38 |
| SIMD tokenizer (8) | 0.3 | 0.59 | 0.87 | 1.23 | 2.08 |
| Direct-coded, re2c (15) | 0.3 | 0.39 | 1.18 | 1.74 | 3.30 |
| Table-driven, flex (30) | 0.3 | 0.22 | 1.49 | 2.29 | 4.97 |

The frontend's Cost Model page implements these formulas live (section 10).

## 8. Evaluation

### 8.1 Phase 0 limit study (Python)

- **Tokenizers:** C: a regex maximal-munch tokenizer in `limitstudy/ctok.py` following section 3's token kinds (comments and whitespace are trivia attached to the next token as leading bytes). Python: stdlib `tokenize`. Both emit `(kind, start, end, text, sigma)`.
- **Simulator:** walks each test file's token stream with the exact predictor logic of section 5.2 (copy table, static order-2 and order-1, 2-bit confidence, W = 32, max 8 tokens per phrase, partial acceptance with the guard rule).
- **Static table mining:** from training files, for each context collect the continuation phrases, keep the most frequent per context, score by `count * tokens_in_phrase`, keep the top entries that fit the budget.
- **Sweeps:** budget {32, 128, 512, 2048} KB; context order {1, 2, 3}; W {16, 32, 64}; predictor config {copy only, static only, both}; kind-only Markov baseline.
- **Output:** `results/limit_study.json` (schema 9.1).
- **Gate:** report coverage and g next to the break-even table in section 7.

### 8.2 Corpus (cloned by `corpus/fetch.py`, shallow, pinned to tags)

| Language | Train projects | Test projects |
| --- | --- | --- |
| C | git, curl, linux (only `kernel/`, `mm/`, `fs/` via sparse checkout) | sqlite, redis, lua, nginx |
| Python | cpython `Lib/`, django | requests, flask, rich |

Adversarial set (generated by `corpus/adversarial.py`): identifiers renamed to random strings, lines shuffled within each function, all whitespace minimized, a generator that alternates two continuations per context to thrash confidence, and files under 1 KB.

### 8.3 Metrics

Throughput (MB/s and M tokens/s), cycles per byte, instructions per byte, branch mispredicts per token, L1D and L2 misses per KB, coverage, mean tokens per phrase, failed-probe rate g, partial-accept rate, throughput vs bytes into file (cold start), predictor memory. 30 runs per configuration on a pinned core; report median and 95% CI; aggregate across files with byte-weighted geometric means.

### 8.4 Ablations

Copy only; static only; kind-only Markov contexts; no partial acceptance; no guard classes (exact guard bytes only); no intern-ID caching; no successor prefetch; governor off; W = 16 and W = 64.

### 8.5 Correctness

- `difftest`: for every corpus file, compare PLAB vs baseline arrays element by element (kind, start, len, id, sigma) and the final line count. Print the first divergence with 40 bytes of context.
- Fuzzing: libFuzzer (clang) or a Python mutation fuzzer on Windows; mutations concentrated at token boundaries and on the bytes in `EXTENDS` sets.
- Regressions: every failing input is saved in `core/tests/regressions/` and replayed by `ctest`.

## 9. Results JSON schemas

Every file has `meta`: `{ "commit": str, "date": str, "machine": str, "cpu": str, "compiler": str, "flags": str, "runs": int }`.

### 9.1 `results/limit_study.json`

```json
{
  "meta": {},
  "cost_model_assumptions": { "C_hit": 10, "n": 4, "C_ctx": 1, "C_p": 6, "P_br": 17 },
  "runs": [
    {
      "lang": "c", "predictor": "both", "budget_kb": 512, "order": 2, "W": 32,
      "files": 812, "tokens": 9134221, "bytes": 41233019,
      "coverage_tokens": 0.0, "coverage_bytes": 0.0,
      "mean_tokens_per_phrase": 0.0, "failed_probe_rate": 0.0, "partial_accept_rate": 0.0,
      "by_source": { "copy": 0.0, "static_o2": 0.0, "static_o1": 0.0 },
      "phrase_len_hist": [0, 0, 0, 0, 0, 0, 0, 0]
    }
  ]
}
```

### 9.2 `results/bench.json`

```json
{
  "meta": {},
  "rows": [
    {
      "lang": "c", "corpus": "test", "lexer": "re2c", "plab": true, "config": "default",
      "mb_s": { "median": 0.0, "ci95": [0.0, 0.0] },
      "mtok_s": { "median": 0.0, "ci95": [0.0, 0.0] },
      "cycles_per_byte": 0.0, "instr_per_byte": 0.0,
      "branch_miss_per_tok": null, "l1d_miss_per_kb": null,
      "coverage_tokens": 0.0
    }
  ]
}
```

Hardware-counter fields are `null` when not measured (Windows).

### 9.3 `web/public/traces/index.json` and `web/public/traces/<name>.json`

```json
{ "files": [ { "name": "sqlite_btree", "path": "sqlite/src/btree.c", "bytes": 0, "tokens": 0, "coverage": 0.0 } ] }
```

```json
{
  "meta": {}, "name": "sqlite_btree", "source": "full file text",
  "tokens": [
    { "s": 0, "e": 7, "k": "keyword", "o": "commit", "ph": 12, "src": "copy", "conf": 3 }
  ],
  "phrases": [ { "id": 12, "s": 0, "e": 31, "ntok": 6, "accepted": 6, "src": "copy", "mismatch_at": null } ]
}
```

Token outcome `o` is one of `commit` (full phrase accepted), `partial` (committed from a partially matching phrase), `miss` (a probe was made and failed, then fallback), `fallback` (no confident prediction, baseline only). `ph` is the phrase ID or `null`.

## 10. Frontend specification (`web/`)

Stack: Vite, React 18, TypeScript strict, Tailwind CSS, Recharts, React Router. No backend: the app reads JSON from `web/public/results/` (copied from `results/` by `npm run sync`) and `web/public/traces/`. Fonts: Inter for UI, JetBrains Mono for code. Light and dark themes with a toggle (remember the choice in `localStorage`, wrapped in try/catch).

**Fixed color meaning, used on every page:** committed = green, partial = teal, failed probe = amber, fallback = neutral grey, accent = blue for the thing a chart is about. A small legend component shows this everywhere it is used.

Layout: left sidebar navigation with the five pages, top bar with the dataset `meta` (machine, commit, date). Responsive down to 1024 px wide; the token inspector may require a wide screen.

### Page 1: Overview
- KPI cards: token coverage (C, Python), mean tokens per phrase, best speedup vs re2c, adversarial worst-case slowdown, exactness status ("N files, 0 divergences" from a `results/difftest.json` with `{files, divergences}`).
- One-sentence finding at the top generated from the data, for example "PLAB commits 61% of C tokens through prediction, 4.2 tokens per phrase".
- Small table: language x predictor config with coverage.

### Page 2: Limit Study
- Line chart: coverage vs budget (log x axis), one line per predictor config, with horizontal reference lines at the break-even coverage for each baseline (from section 7, recomputed with the measured g).
- Grouped bars: coverage by context order and W.
- Histogram: accepted tokens per phrase.
- Stacked bar: share of commits by source (copy, static order-2, static order-1).
- Filters: language, predictor config.

### Page 3: Benchmarks
- Grouped bar chart: MB/s per test project, bars for baseline alone vs PLAB over baseline, with 95% CI whiskers.
- Speedup chart: PLAB/baseline ratio per project, reference line at 1.0.
- Table: cycles per byte, instructions per byte, mispredicts per token, cache misses (shows "not measured" for null).
- Adversarial panel: slowdown per adversarial input with a red reference line at 5%.
- Ablation panel: speedup per ablation vs default.

### Page 4: Token Inspector (the showcase page)
- File picker from `traces/index.json` with coverage shown per file.
- Source view in monospace with line numbers. Each token's background tinted by outcome color. Accepted phrases get an underline band spanning the phrase; the band color shows the predictor source.
- Hover card on a token: kind, byte range, outcome, phrase ID, predictor source, confidence, phrase length, and for misses the mismatch offset with the expected vs actual byte.
- Right panel: file stats (coverage, tokens per phrase, misses), a mini bar of outcomes, and a list of the 20 most frequent committed phrases in the file (click to highlight all occurrences).
- Toggles: show phrases, show only misses, dim fallback tokens.
- Performance: render lines lazily (only visible lines plus a buffer) so a 10,000-line file stays smooth.

### Page 5: Cost Model
- Sliders: C_ref, C_hit, n, C_ctx, C_p, P_br, g; preset buttons for SIMD (8), re2c (15), flex (30).
- Line chart of S(a) for a in [0, 1] with the break-even point marked and labeled.
- Vertical markers for measured coverage per language from the limit study, so the user can read predicted speedup directly.
- A formula block showing F, S(a) and a* with the current numbers substituted.

### Frontend quality bar
- No mock data in the final build; while Phase 0 runs, use `web/public/results/sample/` clearly labeled "sample data" in the top bar.
- Every chart has a title stating the finding, axis units, and a source line naming the JSON file.
- Empty and loading states for every page; a clear error if a JSON file is missing.
- `npm run build` must pass with zero TypeScript errors.

## 11. Glossary

| Term | Meaning |
| --- | --- |
| Phrase | Up to 8 consecutive tokens (max W = 32 bytes) recorded from a token end, including leading whitespace |
| Coverage | Fraction of tokens committed through prediction rather than by the baseline |
| Context | Identity of the last two tokens plus sigma, hashed |
| Copy predictor | Proposes what followed the same context earlier in the same file |
| Static table | Phrases mined offline from a training corpus |
| Guard | The byte after a committed token, checked so the token cannot be longer |
| sigma | Exact lexer mode bits that a phrase's validity depends on |
| Governor | Per-window switch that turns prediction off when it is not paying for itself |
