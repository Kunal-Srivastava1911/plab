/* PLAB engine: probe, verify, partial accept, commit, train, govern (spec sections 3, 5, 6). */
#include <stdlib.h>
#include <string.h>

#include "plab.h"
#include "lex_inline.h"
#include <x86intrin.h>

#if defined(__AVX2__)
#include <immintrin.h>
static inline uint32_t mask_eq32(const uint8_t *a, const uint8_t *b) {
    __m256i x = _mm256_loadu_si256((const __m256i *)a);
    __m256i y = _mm256_loadu_si256((const __m256i *)b);
    return (uint32_t)_mm256_movemask_epi8(_mm256_cmpeq_epi8(x, y));
}
static inline uint32_t mask_byte32(const uint8_t *a, uint8_t c) {
    __m256i x = _mm256_loadu_si256((const __m256i *)a);
    return (uint32_t)_mm256_movemask_epi8(_mm256_cmpeq_epi8(x, _mm256_set1_epi8((char)c)));
}
#else
static inline uint32_t mask_eq32(const uint8_t *a, const uint8_t *b) {
    uint32_t m = 0;
    for (int i = 0; i < 32; i++) m |= (uint32_t)(a[i] == b[i]) << i;
    return m;
}
static inline uint32_t mask_byte32(const uint8_t *a, uint8_t c) {
    uint32_t m = 0;
    for (int i = 0; i < 32; i++) m |= (uint32_t)(a[i] == c) << i;
    return m;
}
#endif

#define PREFETCH(p) __builtin_prefetch((p), 0, 3)

static inline uint32_t low_mask(uint32_t n) { return n >= 32 ? 0xFFFFFFFFu : (1u << n) - 1; }

plab_config plab_default_config(void) {
    plab_config c = {.use_copy = 1, .use_static = 1, .partial = 1, .guard_class = 1, .intern_cache = 1,
                     .prefetch = 1, .governor = 1, .W = PLAB_W, .copy_cascade = 1, .copy_conf_min = 1,
                     .train_committed = 1, .train_every = 1};
    return c;
}

int plab_make_record(plab_rec *r, const uint8_t *src, const plab_tokens *t, uint32_t i,
                     uint32_t last, uint32_t W, uint16_t sigma_in) {
    uint32_t base = i == UINT32_MAX ? 0 : t->start[i] + t->len[i];
    uint32_t first = i + 1; /* wraps to 0 for the start of file */
    uint32_t n = 0, ends = 0, L = 0;
    for (uint32_t k = first; k <= last && n < PLAB_MAXTOK; k++) {
        uint8_t kind = t->kind[k];
        if (kind == TK_HEADER_NAME || kind == TK_UNKNOWN) break;
        uint32_t e = t->start[k] + t->len[k] - base;
        if (e > W) break;
        r->desc[n] = (uint16_t)(e << 10 | kind);
        r->start_off[n] = (uint8_t)(t->start[k] - base);
        r->sig_tok[n] = (uint8_t)(t->sigma[k] | plab_sigma_after(t->sigma[k], kind, t->id[k]) << 4);
        ends |= 1u << (e - 1);
        L = e;
        n++;
        if (kind == TK_PP_END) break; /* a directive end is only ever the last token */
    }
    if (!n) return 0;
    memcpy(r->bytes, src + base, 32);
    /* never record line splices: a backslash followed by a newline or CR */
    uint32_t bs = mask_byte32(r->bytes, '\\') & low_mask(L);
    while (bs) {
        uint32_t b = (uint32_t)__builtin_ctz(bs);
        uint8_t nx = b + 1 < 32 ? r->bytes[b + 1] : src[base + b + 1];
        if (nx == '\n' || nx == '\r') {
            /* keep the tokens that end before the splice */
            uint32_t keep = (uint32_t)__builtin_popcount(ends & low_mask(b));
            uint32_t m = 0;
            while (m < keep && (r->desc[m] >> 10) <= b) m++;
            if (!m) return 0;
            n = m;
            L = r->desc[n - 1] >> 10;
            ends &= low_mask(L);
            break;
        }
        bs &= bs - 1;
    }
    r->len = (uint8_t)L;
    r->ntok = (uint8_t)n;
    r->ends = ends;
    r->sigma_in = sigma_in;
    r->sigma_out = r->sig_tok[n - 1] >> 4;
    r->nlmask = mask_byte32(r->bytes, '\n') & low_mask(L);
    r->newlines = (uint8_t)__builtin_popcount(r->nlmask);
    for (uint32_t k = n; k < PLAB_MAXTOK; k++) { r->desc[k] = 0; r->start_off[k] = 0; r->sig_tok[k] = 0; }
    return (int)n;
}

int plab_engine_init(plab_engine *e, const plab_table *tab, plab_config cfg) {
    memset(e, 0, sizeof *e);
    plab_init();
    e->tab = tab;
    e->cfg = cfg;
    e->kind_only = tab && (tab->flags & PLAB_TABLE_KIND_ONLY);
    e->gov_pref = -1;
    e->gov_interval = 32;
    if (!tab || !tab->n2) e->cfg.use_static = cfg.use_static && tab && tab->n1;
    uint32_t n2 = tab ? tab->n2 : 0, n1 = tab ? tab->n1 : 0;
    e->sconf2 = calloc(n2 + n1 + 1, 1);
    e->sconf1 = e->sconf2 + n2;
    e->iconf = calloc(n2 + n1 + 1, 1);
    e->key2 = calloc(n2 + n1 + 1, sizeof(uint32_t));
    e->key1 = e->key2 + n2;
    for (uint32_t i = 0; i < n2 + n1; i++) {
        const plab_rec *r = &tab->o2[i]; /* o1 follows o2 in one allocation */
        e->iconf[i] = r->conf;
        e->key2[i] = r->len ? 1u << 31 | (uint32_t)r->sigma_in << 16 | r->tag : 0;
    }
    return plab_interner_init(&e->in);
}

void plab_engine_free(plab_engine *e) {
    plab_interner_free(&e->in);
    free(e->sconf2);
    free(e->iconf);
    free(e->key2);
}

static void reset_run(plab_engine *e) {
    plab_interner_reset(&e->in);
    e->ring_n = 0;
    e->pred_dirty = 1; /* predictor state is cleared lazily, at the first speculative window */
}

static void reset_predictors(plab_engine *e) {
    memset(e->copy, 0, sizeof e->copy);
    e->ring_n = 0;
    if (e->tab) memcpy(e->sconf2, e->iconf, e->tab->n2 + e->tab->n1);
    e->pred_dirty = 0;
}

/* copy tables: cascade = order 3 (N/2 entries), order 2 (N/4), order 1 (N/4); else order 2 (N) */
#define CN PLAB_COPY_N
static const uint32_t LVL_OFF[2][3] = {{0, 0, 0}, {0, CN / 2, CN / 2 + CN / 4}};
static const uint32_t LVL_MASK[2][3] = {{CN - 1, 0, 0}, {CN / 2 - 1, CN / 4 - 1, CN / 4 - 1}};

static inline uint8_t token_fp(const plab_tokens *t, uint32_t i) {
    uint32_t x = t->kind[i] * 0x9E3779B1u ^ t->len[i] * 0x85EBCA77u ^ t->id[i] * 0xC2B2AE3Du;
    return (uint8_t)(x >> 24);
}

/* the entry is enqueued with ti + 1 < count, so the fingerprint of the next token always exists */
static void flush_ring(plab_engine *e, const plab_tokens *t) {
    const int cas = e->cfg.copy_cascade;
    for (uint32_t r = 0; r < e->ring_n; r++) {
        uint64_t h = e->ring[r].h;
        uint32_t ti = e->ring[r].ti, lvl = e->ring[r].lvl;
        uint8_t fp = token_fp(t, ti + 1);
        plab_copy_ent *c = &e->copy[LVL_OFF[cas][lvl] + ((uint32_t)h & LVL_MASK[cas][lvl])];
        uint16_t tag = plab_tag(h);
        /* branch-free update: tag and fingerprint matches are unpredictable */
        plab_copy_ent o = *c, n = o;
        uint32_t conf = o.cs & 3u;
        uint32_t hit = o.tag == tag, same = hit & (o.fp == fp), replace = !hit & (conf == 0);
        uint32_t inc = conf + (conf < 3), dec = conf - (conf > 0);
        uint32_t nconf = hit ? (same ? inc : dec) : (replace ? 1u : dec);
        uint32_t upd = hit | replace;
        n.tag = replace ? tag : o.tag;
        n.tok_index = upd ? ti : o.tok_index;
        n.fp = upd ? fp : o.fp;
        n.cs = (uint8_t)(nconf | (upd ? (uint32_t)e->ring[r].sig << 4 : (o.cs & 0xF0u)));
        *c = n;
    }
    e->ring_n = 0;
}

/* ---- the hot loop, specialised for tracing at compile time ---- */

typedef struct run_state {
    uint32_t p;
    uint16_t sigma;
    uint32_t c3, c2, c1; /* context identities of the last three tokens */
} run_state;

static inline void ctx_from_tokens(const plab_engine *e, const plab_tokens *t, run_state *s) {
    uint32_t n = t->count;
    s->c1 = n >= 1 ? plab_cid(t, &e->in, n - 1, e->kind_only) : 0;
    s->c2 = n >= 2 ? plab_cid(t, &e->in, n - 2, e->kind_only) : 0;
    s->c3 = n >= 3 ? plab_cid(t, &e->in, n - 3, e->kind_only) : 0;
}

static inline void enqueue(plab_engine *e, const plab_tokens *t, const uint64_t *h, uint32_t ti, uint16_t sig) {
    if (++e->train_ctr & (e->cfg.train_every - 1u)) return; /* sampled training */
    const int nlvl = e->cfg.copy_cascade ? 3 : 1;
    for (int l = 0; l < nlvl; l++) {
        e->ring[e->ring_n].h = h[l];
        e->ring[e->ring_n].ti = ti;
        e->ring[e->ring_n].lvl = (uint8_t)l;
        e->ring[e->ring_n].sig = (uint8_t)sig;
        e->ring_n++;
    }
    if (e->ring_n > PLAB_RING - 3) flush_ring(e, t);
}

static inline void level_hashes(const plab_engine *e, uint32_t c3, uint32_t c2, uint32_t c1, uint16_t sig, uint64_t *h) {
    if (e->cfg.copy_cascade) {
        h[0] = plab_ctx3(c3, c2, c1, sig);
        h[1] = plab_ctx2(c2, c1, sig);
        h[2] = plab_ctx1(c1, sig);
    } else {
        h[0] = plab_ctx2(c2, c1, sig);
    }
}

/* Copy predictor (5.2): the draft is the bytes and tokens that followed the same context earlier
 * in this file. It is verified by comparing the source against itself at the earlier position,
 * then the earlier tokens are committed with their offsets shifted. Returns accepted tokens. */
static inline uint32_t try_copy(plab_engine *e, const uint8_t *src, plab_tokens *t, uint32_t p,
                                uint32_t ti, uint32_t *b_out, uint32_t *ntok_out, uint32_t *a_out) {
    const uint32_t base = t->start[ti] + t->len[ti];
    const uint8_t *at = src + p, *old = src + base;
    uint32_t eq = mask_eq32(at, old);
    uint32_t a = eq == 0xFFFFFFFFu ? 32 : (uint32_t)__builtin_ctz(~eq);
    const uint32_t W = e->cfg.W;
    uint32_t best = 0, bestb = 0, n = 0;
    for (uint32_t k = ti + 1; k < t->count && n < PLAB_MAXTOK; k++) {
        uint8_t kind = t->kind[k];
        if (kind == TK_HEADER_NAME || kind == TK_UNKNOWN) break;
        uint32_t end = t->start[k] + t->len[k] - base;
        if (end > W) break;
        n++;
        if (end <= a) {
            int ok;
            if (e->cfg.guard_class) ok = !plab_extends_has(kind, at[end]);
            else ok = end + 2 <= a; /* exact guard bytes: two bytes of lookahead matched */
            if (ok) { best = n; bestb = end; }
        }
        if (kind == TK_PP_END) break;
    }
    if (!e->cfg.partial && best != n) best = 0;
    *ntok_out = n;
    *a_out = a;
    if (!best) return 0;
    /* commit: copy the earlier tokens, shifting their offsets */
    uint32_t c = t->count, delta = p - base;
    for (uint32_t i = 0; i < best; i++) {
        uint32_t k = ti + 1 + i;
        t->kind[c + i] = t->kind[k];
        t->start[c + i] = t->start[k] + delta;
        t->len[c + i] = t->len[k];
        t->id[c + i] = t->id[k];
        t->sigma[c + i] = t->sigma[k];
    }
    t->count = c + best;
    t->lines += (uint32_t)__builtin_popcount(mask_byte32(at, '\n') & low_mask(bestb));
    *b_out = bestb;
    return best;
}

/* Static tables: returns the record to verify, or NULL. */
static inline const plab_rec *probe_static(plab_engine *e, uint64_t h2, uint64_t h1, uint16_t sigma, uint8_t **slot_conf) {
    const plab_table *tab = e->tab;
    uint32_t want = 1u << 31 | (uint32_t)sigma << 16;
    if (tab->n2) {
        uint32_t idx = (uint32_t)h2 & (tab->n2 - 1);
        if (e->key2[idx] == (want | plab_tag(h2)) && e->sconf2[idx] >= 2) {
            *slot_conf = &e->sconf2[idx];
            return &tab->o2[idx];
        }
    }
    if (tab->n1) {
        uint32_t idx = (uint32_t)h1 & (tab->n1 - 1);
        if (e->key1[idx] == (want | plab_tag(h1)) && e->sconf1[idx] >= 2) {
            *slot_conf = &e->sconf1[idx];
            return &tab->o1[idx];
        }
    }
    return NULL;
}

/* Section 3: commit the longest token prefix whose bytes match and whose guard byte is safe.
 * Returns the number of tokens accepted; *b receives the committed byte length. */
static inline uint32_t accept_len(const plab_engine *e, const plab_rec *r, const uint8_t *at,
                                  uint32_t a, uint32_t *b) {
    uint32_t m;
    if (e->cfg.guard_class) {
        m = r->ends & low_mask(a); /* token ends e <= a: bytes [0, e) verified */
    } else {
        /* exact guard bytes: the next 2 bytes after a token must match the recording */
        uint32_t lim = a < r->len ? a : r->len;
        m = lim >= 2 ? r->ends & low_mask(lim - 2) : 0;
    }
    uint32_t full = r->ends;
    for (int step = 0; m && step < PLAB_MAXTOK; step++) {
        uint32_t hb = 31u - (uint32_t)__builtin_clz(m);
        uint32_t idx = (uint32_t)__builtin_popcount(full & low_mask(hb + 1)) - 1;
        uint32_t end = hb + 1;
        if (!e->cfg.guard_class || !plab_extends_has(r->desc[idx] & 1023, at[end])) {
            if (!e->cfg.partial && idx + 1 != r->ntok) return 0;
            *b = end;
            return idx + 1;
        }
        if (!e->cfg.partial) return 0;
        m &= ~(1u << hb);
    }
    return 0;
}

static inline void commit(plab_engine *e, const plab_rec *r, const uint8_t *src, uint32_t p,
                          uint32_t n, uint32_t b, plab_tokens *t) {
    uint32_t c = t->count;
    int cached = e->cfg.intern_cache && r->epoch == e->in.epoch;
    for (uint32_t i = 0; i < PLAB_MAXTOK; i++) { /* fixed-trip stores; slots >= n are overwritten later */
        uint32_t end = r->desc[i] >> 10, so = r->start_off[i];
        t->kind[c + i] = (uint8_t)(r->desc[i] & 1023);
        t->start[c + i] = p + so;
        t->len[c + i] = end - so;
        t->sigma[c + i] = r->sig_tok[i] & 15;
        t->id[c + i] = r->intern[i];
    }
    if (!cached) {
        for (uint32_t i = 0; i < n; i++) {
            uint8_t k = t->kind[c + i];
            t->id[c + i] = (k == TK_IDENT || k == TK_KEYWORD) ? plab_intern(&e->in, src + t->start[c + i], t->len[c + i]) : 0;
        }
        if (n == r->ntok && e->cfg.intern_cache) {
            plab_rec *w = (plab_rec *)r; /* static records cache IDs per run (5.4) */
            memcpy(w->intern, &t->id[c], n * sizeof(uint32_t));
            w->epoch = e->in.epoch;
        }
    }
    t->count = c + n;
    t->lines += (uint32_t)__builtin_popcount(r->nlmask & low_mask(b));
}

static inline plab_trace_phrase *trace_phrase(plab_engine *e) {
    plab_trace *tr = e->trace;
    if (tr->nphrases == tr->cap) {
        tr->cap = tr->cap ? tr->cap * 2 : 1024;
        tr->phrases = realloc(tr->phrases, tr->cap * sizeof tr->phrases[0]);
    }
    return &tr->phrases[tr->nphrases];
}

static inline void trace_commit(plab_engine *e, uint32_t first, uint32_t n, uint32_t ntok, uint8_t conf) {
    for (uint32_t i = 0; i < n; i++) {
        e->trace->outcome[first + i] = n == ntok ? PLAB_O_COMMIT : PLAB_O_PARTIAL;
        e->trace->phrase[first + i] = (int32_t)e->trace->nphrases;
        e->trace->conf[first + i] = conf;
    }
    e->trace->nphrases++;
}

static inline __attribute__((always_inline)) void run_window(plab_engine *e, const uint8_t *src,
        uint32_t len, uint32_t wend, plab_tokens *t, run_state *s, uint64_t *committed,
        uint64_t *probes, uint64_t *failed, const int trace) {
    const plab_lexer L = {src, len, &e->in};
    const int cas = e->cfg.copy_cascade, nlvl = cas ? 3 : 1;
    while (s->p < wend) {
        uint64_t h[3];
        level_hashes(e, s->c3, s->c2, s->c1, s->sigma, h);
        const uint64_t h2 = cas ? h[1] : h[0];
        int32_t miss_phrase = -1;
        int probed = 0;

        /* copy predictor, longest context first */
        if (e->cfg.use_copy) {
            /* branch-free selection of the longest matching context: tag hits are unpredictable */
            uint32_t sel = UINT32_MAX;
            for (int l = nlvl - 1; l >= 0; l--) {
                uint32_t idx = LVL_OFF[cas][l] + ((uint32_t)h[l] & LVL_MASK[cas][l]);
                const plab_copy_ent *x = &e->copy[idx];
                uint32_t ok = (uint32_t)(x->tag == plab_tag(h[l])) & (uint32_t)((x->cs & 3u) >= e->cfg.copy_conf_min) &
                              (uint32_t)((uint32_t)(x->cs >> 4) == s->sigma);
                sel = ok ? idx : sel;
            }
            if (sel != UINT32_MAX) {
                plab_copy_ent *c = &e->copy[sel];
                probed = 1;
                (*probes)++;
                uint32_t ti = c->tok_index, first = t->count, b = 0, ntok = 0, a = 0;
                uint32_t n = try_copy(e, src, t, s->p, ti, &b, &ntok, &a);
                uint8_t conf = c->cs & 3;
                if (n) {
                    if (trace) {
                        *trace_phrase(e) = (plab_trace_phrase){s->p, s->p + b, (uint8_t)ntok, (uint8_t)n, PLAB_SRC_COPY,
                                                               conf, n < ntok ? (int32_t)a : -1, 0, 0};
                        trace_commit(e, first, n, ntok, conf);
                    }
                    *committed += n;
                    e->stats.phrases++;
                    e->stats.partial += n != ntok;
                    e->stats.by_source[PLAB_SRC_COPY] += n;
                    e->stats.hist[n - 1]++;
                    if (conf < 3) c->cs++;
                    uint32_t last = t->count - 1;
                    s->p += b;
                    s->sigma = plab_sigma_after(t->sigma[last], t->kind[last], t->id[last]);
                    if (e->cfg.train_committed)
                        for (uint32_t k = first; k < last; k++) {
                            if ((e->train_ctr + 1) & (e->cfg.train_every - 1u)) { e->train_ctr++; continue; }
                            uint64_t hk[3];
                            uint16_t sk = plab_sigma_after(t->sigma[k], t->kind[k], t->id[k]);
                            level_hashes(e, k >= 2 ? plab_cid(t, &e->in, k - 2, e->kind_only) : 0,
                                         k >= 1 ? plab_cid(t, &e->in, k - 1, e->kind_only) : 0,
                                         plab_cid(t, &e->in, k, e->kind_only), sk, hk);
                            enqueue(e, t, hk, k, sk);
                        }
                    ctx_from_tokens(e, t, s);
                    continue;
                }
                (*failed)++;
                if (trace) {
                    uint32_t base = t->start[ti] + t->len[ti];
                    *trace_phrase(e) = (plab_trace_phrase){s->p, s->p + (a < 32 ? a + 1 : 32), (uint8_t)ntok, 0, PLAB_SRC_COPY,
                                                           conf, (int32_t)a, src[base + a], src[s->p + a]};
                    miss_phrase = (int32_t)e->trace->nphrases++;
                }
                if (conf) c->cs--;
            }
        }

        /* static tables (only when the copy predictor made no probe) */
        if (!probed && e->cfg.use_static) {
            uint8_t *conf = NULL;
            uint64_t h1 = cas ? h[2] : plab_ctx1(s->c1, s->sigma);
            const plab_rec *r = probe_static(e, h2, h1, s->sigma, &conf);
            if (r) {
                (*probes)++;
                if (e->cfg.prefetch && e->tab->n2) PREFETCH(&e->tab->o2[r->next_ctx & (e->tab->n2 - 1)]);
                const uint8_t *at = src + s->p;
                uint32_t eq = mask_eq32(at, r->bytes) | ~low_mask(r->len);
                uint32_t a = eq == 0xFFFFFFFFu ? 32 : (uint32_t)__builtin_ctz(~eq);
                if (e->cfg.W < 32 && a > e->cfg.W) a = e->cfg.W;
                uint32_t b = 0, n = accept_len(e, r, at, a, &b);
                if (n) {
                    if (trace) {
                        *trace_phrase(e) = (plab_trace_phrase){s->p, s->p + r->len, r->ntok, (uint8_t)n, r->source, *conf,
                                                               a < r->len ? (int32_t)a : -1, 0, 0};
                        trace_commit(e, t->count, n, r->ntok, *conf);
                    }
                    commit(e, r, src, s->p, n, b, t);
                    *committed += n;
                    e->stats.phrases++;
                    e->stats.partial += n != r->ntok;
                    e->stats.by_source[r->source] += n;
                    e->stats.hist[n - 1]++;
                    s->p += b;
                    s->sigma = r->sig_tok[n - 1] >> 4;
                    ctx_from_tokens(e, t, s);
                    if (*conf < 3) (*conf)++;
                    continue;
                }
                (*failed)++;
                if (trace) {
                    uint32_t mis = a < r->len ? a : r->len;
                    *trace_phrase(e) = (plab_trace_phrase){s->p, s->p + r->len, r->ntok, 0, r->source, *conf,
                                                           a < r->len ? (int32_t)a : -1, mis < 32 ? r->bytes[mis] : 0, at[mis]};
                    miss_phrase = (int32_t)e->trace->nphrases++;
                }
                if (*conf) (*conf)--;
            }
        }

        uint32_t before = t->count;
        uint16_t sig_before = s->sigma;
        if (!lex_one_inline(&L, &s->p, &s->sigma, t)) break;
        if (trace) {
            e->trace->outcome[before] = miss_phrase >= 0 ? PLAB_O_MISS : PLAB_O_FALLBACK;
            e->trace->phrase[before] = miss_phrase;
            e->trace->conf[before] = 0;
        }
        s->c3 = s->c2;
        s->c2 = s->c1;
        s->c1 = plab_cid(t, &e->in, before, e->kind_only);
        if (e->cfg.use_copy && before) enqueue(e, t, h, before - 1, sig_before);
    }
}

static inline __attribute__((always_inline)) void run_impl(plab_engine *e, const uint8_t *src,
        uint32_t len, plab_tokens *t, const int trace) {
    reset_run(e);
    t->count = 0;
    t->lines = 0;
    run_state s = {0, PLAB_S_LINE_START, 0, 0, 0};
    const plab_lexer L = {src, len, &e->in};
    int prev_spec = 0;
    while (s.p < len) {
        uint32_t wend = (s.p / PLAB_WINDOW + 1) * PLAB_WINDOW;
        if (wend > len) wend = len;
        /* Governor (6): run the mode with the lower measured cycles per byte, byte-weighted over
         * recent windows of this engine. The other mode is re-measured with exponential backoff
         * (every 32 windows, doubling to every 1024 while the preference holds). */
        int spec = 1;
        if (e->cfg.governor && !trace) {
            e->gov_windows++;
            if (e->gov_bytes[0] < 4096) spec = 0;
            else if (e->gov_bytes[1] < 4096) spec = 1;
            else {
                int pref = e->gov_cyc[1] * e->gov_bytes[0] < e->gov_cyc[0] * e->gov_bytes[1];
                if (pref != e->gov_pref) {
                    e->gov_pref = pref;
                    e->gov_interval = 32;
                    e->gov_next = e->gov_windows + 32;
                }
                spec = pref;
                if (e->gov_windows >= e->gov_next) {
                    spec = !pref;
                    e->gov_next = e->gov_windows + e->gov_interval;
                    if (e->gov_interval < 1024) e->gov_interval *= 2;
                }
            }
        }
        uint32_t p0 = s.p;
        uint64_t c0 = __rdtsc();
        if (spec) {
            uint64_t committed = 0, probes = 0, failed = 0;
            if (e->pred_dirty) reset_predictors(e);
            if (!prev_spec) ctx_from_tokens(e, t, &s);
            run_window(e, src, len, wend, t, &s, &committed, &probes, &failed, trace);
            e->stats.committed += committed;
            e->stats.probes += probes;
            e->stats.failed += failed;
            e->stats.windows_spec++;
        } else {
            /* plain baseline loop: the same code as the baseline alone, no PLAB branches */
            s.p = plab_lex_until(&L, s.p, &s.sigma, t, wend);
            e->stats.windows_base++;
        }
        double dc = (double)(__rdtsc() - c0), db = (double)(s.p - p0);
        e->gov_cyc[spec] = e->gov_cyc[spec] * 0.9 + dc;
        e->gov_bytes[spec] = e->gov_bytes[spec] * 0.9 + db;
        prev_spec = spec;
        if (s.p == p0) break;
    }
    e->stats.tokens += t->count;
}

void plab_run(plab_engine *e, const uint8_t *src, uint32_t len, plab_tokens *t) {
    if (e->trace) run_impl(e, src, len, t, 1);
    else run_impl(e, src, len, t, 0);
}

void plab_run_baseline(plab_interner *in, const uint8_t *src, uint32_t len, plab_tokens *t) {
    plab_interner_reset(in);
    t->count = 0;
    t->lines = 0;
    const plab_lexer L = {src, len, in};
    plab_lex_all(&L, t);
}
