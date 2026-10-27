/* plab_build_table: mine static order-2 and order-1 phrase tables from a training corpus.
 *
 *   plab_build_table --list train.txt --out c.plabt [--o2 2048] [--o1 2048] [--max-mb 32]
 *                    [--kind-only] [--W 32]
 *
 * For every token end in the training files the phrase that follows (<= 8 tokens, <= W bytes)
 * is a candidate. Positions are sorted by (context, phrase bytes), so equal phrase prefixes form
 * contiguous runs; each run is scored count * tokens and the best phrase per context is kept.
 * Contexts are then placed into the direct-mapped tables in score order. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plab.h"

typedef struct file_t {
    uint8_t *src;
    uint32_t len;
    plab_tokens t;
    uint32_t *cid;
} file_t;

typedef struct pos_t {
    uint64_t h;
    uint32_t f, i; /* token index i (UINT32_MAX = start of file) */
    uint32_t ends;
    uint8_t L, ntok;
} pos_t;

static file_t *files;
static uint32_t nfiles;

static const uint8_t *pos_bytes(const pos_t *p) {
    const file_t *f = &files[p->f];
    return f->src + (p->i == UINT32_MAX ? 0 : f->t.start[p->i] + f->t.len[p->i]);
}

static int cmp_pos(const void *a, const void *b) {
    const pos_t *x = a, *y = b;
    if (x->h != y->h) return x->h < y->h ? -1 : 1;
    uint32_t n = x->L < y->L ? x->L : y->L;
    int c = memcmp(pos_bytes(x), pos_bytes(y), n);
    if (c) return c;
    return (int)x->L - (int)y->L;
}

static uint32_t lcp(const pos_t *x, const pos_t *y) {
    const uint8_t *a = pos_bytes(x), *b = pos_bytes(y);
    uint32_t n = x->L < y->L ? x->L : y->L, i = 0;
    while (i < n && a[i] == b[i]) i++;
    return i;
}

typedef struct cand_t {
    uint64_t h;
    uint64_t score;
    uint32_t pos; /* index into the sorted positions */
    uint8_t ntok;
} cand_t;

static int cmp_cand(const void *a, const void *b) {
    const cand_t *x = a, *y = b;
    if (x->score != y->score) return x->score > y->score ? -1 : 1;
    return x->h < y->h ? -1 : x->h > y->h;
}

static uint32_t cid_at(const file_t *f, uint32_t i) { return i == UINT32_MAX ? 0 : f->cid[i]; }

static uint16_t sigma_at(const file_t *f, uint32_t i) {
    return i == UINT32_MAX ? PLAB_S_LINE_START
                           : plab_sigma_after(f->t.sigma[i], f->t.kind[i], f->t.id[i]);
}

/* best phrase per context; returns candidates sorted by score */
static cand_t *mine(pos_t *pos, uint32_t npos, uint32_t *ncand) {
    qsort(pos, npos, sizeof *pos, cmp_pos);
    uint32_t *lc = malloc((npos + 1) * sizeof *lc);
    lc[0] = 0;
    for (uint32_t k = 1; k < npos; k++) lc[k] = pos[k].h == pos[k - 1].h ? lcp(&pos[k - 1], &pos[k]) : 0;
    lc[npos] = 0;
    cand_t *cands = malloc(sizeof *cands * (npos + 1));
    uint32_t nc = 0;
    for (uint32_t g = 0; g < npos;) {
        uint32_t ge = g + 1;
        while (ge < npos && pos[ge].h == pos[g].h) ge++;
        cand_t best = {pos[g].h, 0, 0, 0};
        for (uint32_t x = g; x < ge; x++) {
            uint32_t m = pos[x].ends, j = 0;
            while (m) {
                uint32_t e = (uint32_t)__builtin_ctz(m) + 1;
                m &= m - 1;
                j++;
                if (x > g && lc[x] >= e) continue; /* not the first element of this run */
                uint32_t count = 1;
                for (uint32_t k = x + 1; k < ge && lc[k] >= e; k++) count++;
                uint64_t score = (uint64_t)count * j;
                if (count >= 2 && (score > best.score || (score == best.score && j > best.ntok))) {
                    best.score = score;
                    best.pos = x;
                    best.ntok = (uint8_t)j;
                }
            }
        }
        if (best.score) cands[nc++] = best;
        g = ge;
    }
    free(lc);
    qsort(cands, nc, sizeof *cands, cmp_cand);
    *ncand = nc;
    return cands;
}

static uint32_t fill(plab_rec *tab, uint32_t n, const cand_t *c, uint32_t nc, const pos_t *pos,
                     uint8_t source, uint32_t W) {
    uint32_t used = 0;
    for (uint32_t k = 0; k < nc && used < n; k++) {
        uint32_t slot = (uint32_t)c[k].h & (n - 1);
        if (tab[slot].len) continue;
        const pos_t *p = &pos[c[k].pos];
        const file_t *f = &files[p->f];
        plab_rec *r = &tab[slot];
        uint32_t last = (p->i == UINT32_MAX ? 0 : p->i + 1) + c[k].ntok - 1;
        if (!plab_make_record(r, f->src, &f->t, p->i, last, W, sigma_at(f, p->i))) continue;
        r->tag = plab_tag(c[k].h);
        r->conf = 3;
        r->source = source;
        r->epoch = 0;
        memset(r->intern, 0, sizeof r->intern);
        uint32_t l1 = last, l2 = r->ntok >= 2 ? last - 1 : p->i;
        r->next_ctx = (uint32_t)plab_ctx2(cid_at(f, l2), cid_at(f, l1), r->sigma_out);
        used++;
    }
    return used;
}

static uint32_t rng_state = 12345;
static uint32_t rng(void) { rng_state = rng_state * 1103515245u + 12345u; return rng_state >> 8; }

int main(int argc, char **argv) {
    const char *list = NULL, *out = NULL;
    uint32_t n2 = 2048, n1 = 2048, W = PLAB_W;
    double max_mb = 32;
    int kind_only = 0;
    for (int a = 1; a < argc; a++) {
        if (!strcmp(argv[a], "--list") && a + 1 < argc) list = argv[++a];
        else if (!strcmp(argv[a], "--out") && a + 1 < argc) out = argv[++a];
        else if (!strcmp(argv[a], "--o2") && a + 1 < argc) n2 = (uint32_t)atoi(argv[++a]);
        else if (!strcmp(argv[a], "--o1") && a + 1 < argc) n1 = (uint32_t)atoi(argv[++a]);
        else if (!strcmp(argv[a], "--W") && a + 1 < argc) W = (uint32_t)atoi(argv[++a]);
        else if (!strcmp(argv[a], "--max-mb") && a + 1 < argc) max_mb = atof(argv[++a]);
        else if (!strcmp(argv[a], "--kind-only")) kind_only = 1;
        else { fprintf(stderr, "unknown argument %s\n", argv[a]); return 2; }
    }
    if (!list || !out) {
        fprintf(stderr, "usage: plab_build_table --list files.txt --out table.plabt [--o2 N --o1 N --max-mb MB --kind-only --W 32]\n");
        return 2;
    }
    plab_init();

    /* read the file list and sample it deterministically down to max_mb */
    FILE *lf = fopen(list, "r");
    if (!lf) { perror(list); return 1; }
    char line[4096];
    char **paths = NULL;
    uint32_t npaths = 0, cap = 0;
    while (fgets(line, sizeof line, lf)) {
        line[strcspn(line, "\r\n")] = 0;
        if (!*line) continue;
        if (npaths == cap) { cap = cap ? cap * 2 : 1024; paths = realloc(paths, cap * sizeof *paths); }
        paths[npaths++] = strdup(line);
    }
    fclose(lf);
    for (uint32_t i = npaths; i > 1; i--) { uint32_t j = rng() % i; char *t = paths[i - 1]; paths[i - 1] = paths[j]; paths[j] = t; }

    plab_interner in;
    plab_interner_init(&in);
    files = calloc(npaths, sizeof *files);
    uint64_t total = 0, ntok = 0;
    for (uint32_t i = 0; i < npaths && total < (uint64_t)(max_mb * 1048576); i++) {
        file_t *f = &files[nfiles];
        f->src = plab_read_file(paths[i], &f->len);
        if (!f->src || !f->len) { free(f->src); continue; }
        plab_tokens t;
        plab_tokens_init(&t, f->len);
        plab_interner_reset(&in);
        plab_lexer L = {f->src, f->len, &in};
        plab_lex_all(&L, &t);
        /* shrink to the token count (+8 slack for record reads) */
        uint32_t n = t.count + 8;
        f->t = t;
        f->t.capacity = n;
        f->cid = malloc(n * sizeof *f->cid);
        for (uint32_t k = 0; k < t.count; k++) f->cid[k] = plab_cid(&t, &in, k, kind_only);
        f->t.kind = realloc(t.kind, n);
        f->t.start = realloc(t.start, n * 4ull);
        f->t.len = realloc(t.len, n * 4ull);
        f->t.id = realloc(t.id, n * 4ull);
        f->t.sigma = realloc(t.sigma, n * 2ull);
        total += f->len;
        ntok += t.count;
        nfiles++;
    }
    fprintf(stderr, "training on %u files, %.1f MB, %llu tokens\n", nfiles, total / 1048576.0, (unsigned long long)ntok);

    pos_t *pos = malloc(sizeof *pos * (ntok + nfiles));
    uint32_t npos = 0;
    plab_rec r;
    for (uint32_t fi = 0; fi < nfiles; fi++) {
        file_t *f = &files[fi];
        if (!f->t.count) continue;
        for (uint32_t i = UINT32_MAX; i == UINT32_MAX || i + 1 < f->t.count; i++) {
            int n = plab_make_record(&r, f->src, &f->t, i, f->t.count - 1, W, sigma_at(f, i));
            if (!n) continue;
            pos_t *p = &pos[npos++];
            p->f = fi;
            p->i = i;
            p->ends = r.ends;
            p->L = r.len;
            p->ntok = r.ntok;
            p->h = plab_ctx2(i == UINT32_MAX || i == 0 ? 0 : f->cid[i - 1], cid_at(f, i), sigma_at(f, i));
        }
    }

    plab_table tab;
    if (plab_table_alloc(&tab, n2, n1)) { fprintf(stderr, "out of memory\n"); return 1; }
    tab.flags = kind_only ? PLAB_TABLE_KIND_ONLY : 0;
    uint32_t nc;
    cand_t *c = mine(pos, npos, &nc);
    uint32_t u2 = n2 ? fill(tab.o2, n2, c, nc, pos, PLAB_SRC_O2, W) : 0;
    fprintf(stderr, "order-2: %u candidate contexts, %u/%u slots filled\n", nc, u2, n2);
    free(c);

    for (uint32_t k = 0; k < npos; k++) {
        const file_t *f = &files[pos[k].f];
        pos[k].h = plab_ctx1(cid_at(f, pos[k].i), sigma_at(f, pos[k].i));
    }
    c = mine(pos, npos, &nc);
    uint32_t u1 = n1 ? fill(tab.o1, n1, c, nc, pos, PLAB_SRC_O1, W) : 0;
    fprintf(stderr, "order-1: %u candidate contexts, %u/%u slots filled\n", nc, u1, n1);
    free(c);

    if (plab_table_save(&tab, out)) { perror(out); return 1; }
    fprintf(stderr, "wrote %s (%u + %u records, %zu KB)\n", out, n2, n1, ((size_t)n2 + n1) * sizeof(plab_rec) / 1024);
    return 0;
}
