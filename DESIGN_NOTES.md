# PLAB design notes

Implementation of `PLAB_SPEC.md` (Predictive Lexical Analysis Buffering). The spec is the contract; this file records the layout, how to run things, and every place the implementation deliberately differs from the spec.

## Layout

| Path | What |
| --- | --- |
| `corpus/fetch.py` | Shallow, tag-pinned clones into `corpus/src/` (8.2). Writes `corpus/manifest.json`. |
| `corpus/adversarial.py` | Adversarial set into `corpus/adversarial/{renamed,shuffled,minified,thrash,tiny}`. |
| `limitstudy/` | Phase 0 (8.1): `ctok.py` C tokenizer, `pytok.py` Python tokenizer, `sim.py` predictors and miner, `run.py` sweeps → `results/limit_study.json`. |
| `core/` | C library and tools. `src/lex_inline.h` is the baseline lexer, `src/engine.c` the PLAB hot loop and governor, `src/table.c` `.plabt` I/O, `src/intern.c` the interner. |
| `core/tools/` | `plab_build_table`, `plab_difftest`, `plab_bench`, `plab_trace`. |
| `core/tests/` | `test_lex.c` unit tests, `fuzz.py` mutation fuzzer, `regressions/` replayed by ctest. |
| `scripts/run_all.py` | The whole pipeline: `build lists adversarial tables difftest fuzz bench traces limitstudy sync`. |
| `web/` | Vite + React 18 + TS + Tailwind + Recharts frontend (section 10). |

## Running

```
python corpus/fetch.py                 # once, ~1.5 GB
python scripts/run_all.py              # everything; or name steps, e.g. `tables difftest`
ctest --test-dir core/build            # unit tests + regression replay
cd web && npm install && npm run sync && npm run build   # or npm run dev
```

Toolchain used: MinGW-w64 gcc 16 (UCRT), CMake + Ninja, Python 3.11, Node 24. Build flags `-O2 -march=native` (AVX2 compare; a scalar twin is used without AVX2).

## Deviations from the spec (all intentional)

- **Baseline lexer.** re2c and flex are not installed, so the baseline is a hand-written direct-coded maximal-munch lexer (`core/src/lex_inline.h`), the role re2c plays in the spec. Results label it `lexer: "direct"`. There is no table-driven (flex) baseline.
- **sigma bit 3 (`PLAB_S_DNAME`).** Set right after the directive-introducing `#`, cleared after the next token. Without it, entering `include_mode` depends on the previous token rather than on sigma, which breaks the exactness lemma. Bits 4–15 stay zero.
- **Context identity.** The context hash uses a stable spelling hash for identifiers and keywords (`interner.hash[id]`) instead of the run-local intern ID, so static tables mined offline match at run time. `tokens.id[]` still holds the intern ID.
- **Token buffer capacity** is `source_len + 64`, not `source_len / 2 + 64`: one-byte tokens with no whitespace (`a+b`) exceed half the length.
- **Acceptance uses `b <= a`** (bytes `[0, b)` verified, guard byte read from the actual source) rather than `b < a`. Two-byte lookahead cases (`..`, `%:%`, number `'`) are covered by the EXTENDS sets of the token that would absorb the byte.
- **EXTENDS for C** is derived mechanically from the punctuator list, plus the spec's additions. Beyond the spec table it includes `:` for `:` (C23 `::`), `%` for `%:` (`%:%:`), and `"` `'` for identifiers (prefixed literals `L"…"`, `u8'…'`).
- **Record pad bytes** carry per-token `start_off[8]`, `sig_tok[8]` (sigma before/after) and `nlmask`, needed for exact partial commits. The struct is still 128 bytes.
- **Copy predictor (default `copy_cascade`).** The 4096 entries (32 KB) are split into context orders 3, 2 and 1 (2048/1024/1024), probed longest context first; the probe threshold is confidence >= 1 and the predictor also trains inside committed phrases. This raised limit-study C coverage from 31% to 45%. The spec predictor (order-2 only, confidence >= 2, fallback-only training) is the `spec_predictors` ablation and the `both` limit-study runs.
- **Copy verification** compares the source against itself at the earlier position (one 32-byte compare) and copies the earlier tokens with shifted offsets, instead of materializing a 128-byte draft record. Exact for the same reason as records: same bytes, same sigma, guard byte checked.
- **Copy entry** packs confidence and sigma into one byte (`cs`) and uses the spare byte as an 8-bit fingerprint of the next token, so training never touches old tokens; the entry update and the cascade selection are branch-free.
- **Static-table probe** checks compact L1-resident key arrays (`valid | sigma_in | tag`) before touching a 128-byte record.
- **Governor** measures instead of estimating: per 4 KB window it records TSC cycles and bytes for each mode (decayed sums per engine), runs the cheaper mode, and re-measures the other mode with exponential backoff (every 32 windows, doubling to 1024 while the preference holds). Predictor state is reset lazily, only when a file's first speculative window runs. Replaces the spec's `committed * C_ref - probes * C_p - failed * P_br` estimate, whose assumed constants were far from measured costs.
- **Epochs** are global across interners, so static-record intern caches never alias between engines that share a table.
- **Limit study sampling.** Train and test sets are sampled to 8 MB and 10 MB per language (deterministic seeds). Python uses a token-oracle acceptance (recorded tokens must equal actual tokens) because its tokenizer has no EXTENDS sets; C uses the guard rule. Each run records which one.
- **Hardware counters** (instructions, mispredicts, cache misses) are `null`: there are no perf counters on Windows. Cycles are TSC reference cycles.
- **Commit hash** is `no-git`: the project directory is not a git repository.

## Current results (2026-10-27, i9-14900HX)

- H5 exactness, met: 0 divergences, 2,410 files / 7.3M tokens × 11 configurations, plus 3,000 fuzz cases.
- H1 coverage, not met: cascade predictor 45.0% C / 44.5% Python, 2.25 tokens per phrase (spec predictor: 31% / 1.87). Order, W and budget sweeps plateau at about 45%.
- H2 speed, not met: 0.99× the direct-coded baseline on the C test corpus. With prediction forced on (`governor_off`) it is 0.27×: training the copy predictor at every fallback token costs about 25 cycles against a baseline of about 40 cycles per token, so the measured governor keeps prediction off almost everywhere.
- H3 mechanism: not measurable on Windows (no hardware counters).
- Sampled-training experiment (`train_every`, prediction forced on, C test corpus, baseline 5.29 cycles/byte): the cascade predictor gives 0.27× when training every token, 0.37× at 1 in 4, 0.44× at 1 in 16 and 0.50× at 1 in 64, with coverage falling 45% → 36% → 24% → 16%. Static tables alone, with no training at all, give 0.66× at 10% coverage. The speculative loop's per-token bookkeeping (context hashes, lookup, last-three-token tracking) costs about 10–12 of the baseline's ~37 cycles per token before any prediction, so no software training schedule reaches parity on this machine. Anchor-only prediction (only after `;` `{` `}` and directive ends) was rejected in simulation: 3–24% coverage.
- H4 robustness, met: worst adversarial slowdown 2.3% (minified); thrash 2.0%, shuffled 1.1%, tiny 0.8%, renamed 0.1%. Met because the governor measures that prediction does not pay and switches it off.
