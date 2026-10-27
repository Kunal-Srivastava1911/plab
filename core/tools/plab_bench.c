/* plab_bench: throughput of the baseline alone vs PLAB over the baseline (spec 8.3, 8.4, 9.2).
 *
 *   plab_bench --list groups.txt --table c.plabt [--kind-table c_kind.plabt] [--runs 30]
 *              [--ablation-runs 15] [--out bench.json] [--meta meta.json]
 *
 * groups.txt lines are "corpus:project<TAB>path". Every group is measured with the baseline and
 * with PLAB (default config), runs interleaved. Ablations run over all files of corpus "test".
 * Hardware counters are not available on Windows, so those fields are null. */
#include <x86intrin.h>

#include "common.h"

typedef struct src_t { uint8_t *src; uint32_t len; } src_t;

typedef struct group_t {
    char corpus[64], project[128];
    src_t *f;
    uint32_t n, cap;
    uint64_t bytes;
} group_t;

typedef struct sample_t { double mb_s, mtok_s, cyc_per_byte; } sample_t;

static plab_tokens toks;
static plab_interner bin;

static uint64_t run_group(const group_t *g, plab_engine *e, uint64_t *cycles, double *sec) {
    uint64_t ntok = 0;
    double t0 = now_sec();
    uint64_t c0 = __rdtsc();
    for (uint32_t i = 0; i < g->n; i++) {
        if (e) plab_run(e, g->f[i].src, g->f[i].len, &toks);
        else plab_run_baseline(&bin, g->f[i].src, g->f[i].len, &toks);
        ntok += toks.count;
    }
    *cycles = __rdtsc() - c0;
    *sec = now_sec() - t0;
    return ntok;
}

static int cmp_d(const void *a, const void *b) {
    double x = *(const double *)a, y = *(const double *)b;
    return x < y ? -1 : x > y;
}

/* median and a distribution-free 95% CI for the median from order statistics */
static void summarize(double *v, int n, double *med, double *lo, double *hi) {
    qsort(v, (size_t)n, sizeof *v, cmp_d);
    *med = n % 2 ? v[n / 2] : 0.5 * (v[n / 2 - 1] + v[n / 2]);
    double r = 0.98 * __builtin_sqrt((double)n);
    int j = (int)(n / 2.0 - r), k = (int)(n / 2.0 + 1 + r + 0.999);
    if (j < 1) j = 1;
    if (k > n) k = n;
    *lo = v[j - 1];
    *hi = v[k - 1];
}

static FILE *jo;
static int first_row = 1;

static void emit_row(const char *corpus, const char *project, int plab, const char *config, sample_t *s,
                     int n, double coverage, double speedup) {
    double *mb = malloc(sizeof(double) * n), *mt = malloc(sizeof(double) * n), *cy = malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) { mb[i] = s[i].mb_s; mt[i] = s[i].mtok_s; cy[i] = s[i].cyc_per_byte; }
    double m1, l1, h1, m2, l2, h2, m3, l3, h3;
    summarize(mb, n, &m1, &l1, &h1);
    summarize(mt, n, &m2, &l2, &h2);
    summarize(cy, n, &m3, &l3, &h3);
    fprintf(jo, "%s\n    {\"lang\": \"c\", \"corpus\": \"%s\", \"project\": \"%s\", \"lexer\": \"direct\", \"plab\": %s, "
                "\"config\": \"%s\", \"mb_s\": {\"median\": %.3f, \"ci95\": [%.3f, %.3f]}, "
                "\"mtok_s\": {\"median\": %.3f, \"ci95\": [%.3f, %.3f]}, \"cycles_per_byte\": %.4f, "
                "\"instr_per_byte\": null, \"branch_miss_per_tok\": null, \"l1d_miss_per_kb\": null, "
                "\"coverage_tokens\": %.6f, \"speedup\": %s",
            first_row ? "" : ",", corpus, project, plab ? "true" : "false", config, m1, l1, h1, m2, l2, h2, m3,
            coverage, plab ? "" : "null");
    if (plab) fprintf(jo, "%.4f", speedup);
    fprintf(jo, ", \"runs\": %d}", n);
    first_row = 0;
    fprintf(stderr, "  %-12s %-22s %-20s %8.1f MB/s  %6.2f cyc/B  cov %.3f\n", corpus, project, config, m1, m3, coverage);
    free(mb); free(mt); free(cy);
}

static double median_mb(sample_t *s, int n) {
    double *v = malloc(sizeof(double) * n), m, lo, hi;
    for (int i = 0; i < n; i++) v[i] = s[i].mb_s;
    summarize(v, n, &m, &lo, &hi);
    free(v);
    return m;
}

static void sample(const group_t *g, plab_engine *e, sample_t *out) {
    uint64_t cyc;
    double sec;
    uint64_t ntok = run_group(g, e, &cyc, &sec);
    out->mb_s = g->bytes / 1e6 / sec;
    out->mtok_s = ntok / 1e6 / sec;
    out->cyc_per_byte = (double)cyc / (double)g->bytes;
}

/* coverage over the timed runs since `before` (with the governor on, this is what actually ran) */
static double coverage_since(const plab_engine *e, const plab_stats *before) {
    uint64_t tok = e->stats.tokens - before->tokens, com = e->stats.committed - before->committed;
    return tok ? (double)com / tok : 0.0;
}

int main(int argc, char **argv) {
    const char *list = NULL, *tpath = NULL, *kpath = NULL, *out = "bench.json", *meta = NULL;
    int runs = 30, aruns = 15;
    for (int a = 1; a < argc; a++) {
        if (!strcmp(argv[a], "--list") && a + 1 < argc) list = argv[++a];
        else if (!strcmp(argv[a], "--table") && a + 1 < argc) tpath = argv[++a];
        else if (!strcmp(argv[a], "--kind-table") && a + 1 < argc) kpath = argv[++a];
        else if (!strcmp(argv[a], "--out") && a + 1 < argc) out = argv[++a];
        else if (!strcmp(argv[a], "--meta") && a + 1 < argc) meta = argv[++a];
        else if (!strcmp(argv[a], "--runs") && a + 1 < argc) runs = atoi(argv[++a]);
        else if (!strcmp(argv[a], "--ablation-runs") && a + 1 < argc) aruns = atoi(argv[++a]);
        else { fprintf(stderr, "unknown argument %s\n", argv[a]); return 2; }
    }
    file_list fl;
    if (!list || read_list(list, &fl)) { fprintf(stderr, "need --list groups.txt\n"); return 2; }
    plab_init();
    pin_thread();
    plab_table tab = {0}, ktab = {0};
    if (!tpath || plab_table_load(&tab, tpath)) { fprintf(stderr, "cannot load table\n"); return 2; }
    if (kpath && plab_table_load(&ktab, kpath)) { fprintf(stderr, "cannot load %s\n", kpath); return 2; }

    /* load groups; "test" collects every test-corpus file for the ablations */
    group_t *groups = calloc(fl.n + 1, sizeof *groups);
    uint32_t ng = 0, maxlen = 0;
    group_t all = {"test", "all", NULL, 0, 0, 0};
    for (uint32_t i = 0; i < fl.n; i++) {
        char *colon = strchr(fl.group[i], ':');
        if (!colon) continue;
        *colon = 0;
        group_t *g = NULL;
        for (uint32_t k = 0; k < ng; k++)
            if (!strcmp(groups[k].corpus, fl.group[i]) && !strcmp(groups[k].project, colon + 1)) g = &groups[k];
        if (!g) {
            g = &groups[ng++];
            snprintf(g->corpus, sizeof g->corpus, "%s", fl.group[i]);
            snprintf(g->project, sizeof g->project, "%s", colon + 1);
        }
        src_t s;
        s.src = plab_read_file(fl.path[i], &s.len);
        if (!s.src || !s.len) continue;
        if (s.len > maxlen) maxlen = s.len;
        group_t *dst[2] = {g, !strcmp(g->corpus, "test") ? &all : NULL};
        for (int d = 0; d < 2; d++) {
            if (!dst[d]) continue;
            if (dst[d]->n == dst[d]->cap) {
                dst[d]->cap = dst[d]->cap ? dst[d]->cap * 2 : 64;
                dst[d]->f = realloc(dst[d]->f, dst[d]->cap * sizeof(src_t));
            }
            dst[d]->f[dst[d]->n++] = s;
            dst[d]->bytes += s.len;
        }
    }
    plab_tokens_init(&toks, maxlen);
    plab_interner_init(&bin);

    jo = fopen(out, "w");
    if (!jo) { perror(out); return 2; }
    char *metas = read_meta(meta);
    fprintf(jo, "{\n  \"meta\": %s,\n  \"rows\": [", metas);

    named_config cfgs[16];
    int ncfg = ablation_configs(cfgs);
    plab_engine def;
    plab_engine_init(&def, &tab, cfgs[0].cfg);
    sample_t *sb = malloc(sizeof(sample_t) * (size_t)(runs > aruns ? runs : aruns));
    sample_t *sp = malloc(sizeof(sample_t) * (size_t)(runs > aruns ? runs : aruns));

    fprintf(stderr, "benchmarking %u groups, %d runs each\n", ng, runs);
    for (uint32_t k = 0; k < ng; k++) {
        group_t *g = &groups[k];
        if (!g->n) continue;
        sample(g, NULL, &sb[0]); /* warm up */
        sample(g, &def, &sp[0]);
        plab_stats before = def.stats;
        for (int r = 0; r < runs; r++) {
            sample(g, NULL, &sb[r]);
            sample(g, &def, &sp[r]);
        }
        double cov = coverage_since(&def, &before);
        double mbase = median_mb(sb, runs), mplab = median_mb(sp, runs);
        emit_row(g->corpus, g->project, 0, "baseline", sb, runs, 0.0, 0);
        emit_row(g->corpus, g->project, 1, "default", sp, runs, cov, mplab / mbase);
    }

    if (all.n) {
        fprintf(stderr, "ablations over %u test files (%.1f MB), %d runs each\n", all.n, all.bytes / 1e6, aruns);
        for (int r = 0; r < aruns; r++) sample(&all, NULL, &sb[r]);
        double mbase = median_mb(sb, aruns);
        emit_row("test", "all", 0, "baseline", sb, aruns, 0.0, 0);
        for (int c = 0; c < ncfg; c++) {
            if (cfgs[c].kind_only && !kpath) continue;
            plab_engine e;
            plab_engine_init(&e, cfgs[c].kind_only ? &ktab : &tab, cfgs[c].cfg);
            sample(&all, &e, &sp[0]);
            plab_stats before = e.stats;
            for (int r = 0; r < aruns; r++) sample(&all, &e, &sp[r]);
            double cov = coverage_since(&e, &before);
            emit_row("test", "all", 1, cfgs[c].name, sp, aruns, cov, median_mb(sp, aruns) / mbase);
            plab_engine_free(&e);
        }
    }
    fprintf(jo, "\n  ]\n}\n");
    fclose(jo);
    fprintf(stderr, "wrote %s\n", out);
    return 0;
}
