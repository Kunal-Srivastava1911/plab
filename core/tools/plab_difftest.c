/* plab_difftest: PLAB vs baseline token arrays, element by element (spec 8.5).
 *
 *   plab_difftest --list files.txt [--table c.plabt] [--kind-table c_kind.plabt]
 *                 [--configs default|all] [--out difftest.json] [--meta meta.json] [--quiet]
 *   plab_difftest --table c.plabt file1.c file2.c ...
 *
 * Exit status 1 if any divergence was found. */
#include "common.h"

static uint8_t *esc_ctx(const uint8_t *src, uint32_t len, uint32_t at, char *buf) {
    uint32_t a = at > 20 ? at - 20 : 0, b = at + 20 < len ? at + 20 : len, k = 0;
    for (uint32_t i = a; i < b; i++) {
        uint8_t c = src[i];
        if (i == at) { buf[k++] = '|'; }
        if (c == '\n') { buf[k++] = '\\'; buf[k++] = 'n'; }
        else if (c < 0x20 || c >= 0x7F) buf[k++] = '.';
        else buf[k++] = (char)c;
    }
    buf[k] = 0;
    return (uint8_t *)buf;
}

/* returns the index of the first divergence, or -1 */
static int64_t compare(const plab_tokens *a, const plab_tokens *b) {
    uint32_t n = a->count < b->count ? a->count : b->count;
    for (uint32_t i = 0; i < n; i++)
        if (a->kind[i] != b->kind[i] || a->start[i] != b->start[i] || a->len[i] != b->len[i] ||
            a->id[i] != b->id[i] || a->sigma[i] != b->sigma[i])
            return i;
    if (a->count != b->count) return n;
    if (a->lines != b->lines) return a->count;
    return -1;
}

int main(int argc, char **argv) {
    const char *list = NULL, *tpath = NULL, *kpath = NULL, *out = NULL, *meta = NULL;
    int all = 1, quiet = 0;
    file_list fl = {0};
    uint32_t extra_cap = 0;
    for (int a = 1; a < argc; a++) {
        if (!strcmp(argv[a], "--list") && a + 1 < argc) list = argv[++a];
        else if (!strcmp(argv[a], "--table") && a + 1 < argc) tpath = argv[++a];
        else if (!strcmp(argv[a], "--kind-table") && a + 1 < argc) kpath = argv[++a];
        else if (!strcmp(argv[a], "--out") && a + 1 < argc) out = argv[++a];
        else if (!strcmp(argv[a], "--meta") && a + 1 < argc) meta = argv[++a];
        else if (!strcmp(argv[a], "--configs") && a + 1 < argc) all = strcmp(argv[++a], "default") != 0;
        else if (!strcmp(argv[a], "--quiet")) quiet = 1;
        else {
            if (fl.n == extra_cap) {
                extra_cap = extra_cap ? extra_cap * 2 : 64;
                fl.path = realloc(fl.path, extra_cap * sizeof *fl.path);
                fl.group = realloc(fl.group, extra_cap * sizeof *fl.group);
            }
            fl.group[fl.n] = "";
            fl.path[fl.n++] = argv[a];
        }
    }
    if (list && read_list(list, &fl)) { perror(list); return 2; }
    plab_init();
    plab_table tab = {0}, ktab = {0};
    if (tpath && plab_table_load(&tab, tpath)) { fprintf(stderr, "cannot load %s\n", tpath); return 2; }
    if (kpath && plab_table_load(&ktab, kpath)) { fprintf(stderr, "cannot load %s\n", kpath); return 2; }

    named_config cfgs[16];
    int ncfg = ablation_configs(cfgs);
    if (!all) ncfg = 1;
    plab_engine *eng = calloc((size_t)ncfg, sizeof *eng);
    int *active = calloc((size_t)ncfg, sizeof *active);
    uint64_t *div = calloc((size_t)ncfg, sizeof *div);
    for (int c = 0; c < ncfg; c++) {
        const plab_table *t = cfgs[c].kind_only ? (kpath ? &ktab : NULL) : (tpath ? &tab : NULL);
        if (cfgs[c].kind_only && !kpath) continue;
        active[c] = 1;
        plab_engine_init(&eng[c], t, cfgs[c].cfg);
    }

    plab_interner bin;
    plab_interner_init(&bin);
    uint64_t files = 0, tokens = 0, bytes = 0, divergences = 0;
    FILE *jo = out ? fopen(out, "w") : NULL;
    if (out && !jo) { perror(out); return 2; }
    char *metas = read_meta(meta);
    if (jo) fprintf(jo, "{\n  \"meta\": %s,\n  \"first_divergences\": [", metas);
    int first_out = 1;

    for (uint32_t fi = 0; fi < fl.n; fi++) {
        uint32_t len;
        uint8_t *src = plab_read_file(fl.path[fi], &len);
        if (!src) { fprintf(stderr, "cannot read %s\n", fl.path[fi]); continue; }
        plab_tokens base, got;
        plab_tokens_init(&base, len);
        plab_tokens_init(&got, len);
        plab_run_baseline(&bin, src, len, &base);
        files++;
        tokens += base.count;
        bytes += len;
        for (int c = 0; c < ncfg; c++) {
            if (!active[c]) continue;
            plab_run(&eng[c], src, len, &got);
            int64_t d = compare(&base, &got);
            if (d < 0) continue;
            divergences++;
            div[c]++;
            uint32_t at = (uint32_t)d < base.count ? base.start[d] : len;
            char ctx[256];
            esc_ctx(src, len, at, (char *)ctx);
            fprintf(stderr, "DIVERGENCE %s [%s] token %lld at byte %u: \"%s\"\n", fl.path[fi], cfgs[c].name,
                    (long long)d, at, ctx);
            if ((uint32_t)d < base.count && (uint32_t)d < got.count)
                fprintf(stderr, "  baseline kind=%s start=%u len=%u id=%u sigma=%u | plab kind=%s start=%u len=%u id=%u sigma=%u\n",
                        plab_kind_name(base.kind[d]), base.start[d], base.len[d], base.id[d], base.sigma[d],
                        plab_kind_name(got.kind[d]), got.start[d], got.len[d], got.id[d], got.sigma[d]);
            else
                fprintf(stderr, "  counts baseline=%u plab=%u lines baseline=%u plab=%u\n", base.count, got.count, base.lines, got.lines);
            if (jo) {
                fprintf(jo, "%s\n    {\"file\": ", first_out ? "" : ",");
                json_str(jo, fl.path[fi]);
                fprintf(jo, ", \"config\": \"%s\", \"token\": %lld, \"byte\": %u, \"context\": ", cfgs[c].name, (long long)d, at);
                json_str(jo, ctx);
                fputc('}', jo);
                first_out = 0;
            }
        }
        if (!quiet && files % 200 == 0) fprintf(stderr, "%llu files...\n", (unsigned long long)files);
        plab_tokens_free(&base);
        plab_tokens_free(&got);
        free(src);
    }

    printf("difftest: %llu files, %llu tokens, %.1f MB, %d configs, %llu divergences\n",
           (unsigned long long)files, (unsigned long long)tokens, bytes / 1048576.0, ncfg,
           (unsigned long long)divergences);
    if (jo) {
        fprintf(jo, "\n  ],\n  \"files\": %llu,\n  \"tokens\": %llu,\n  \"bytes\": %llu,\n  \"divergences\": %llu,\n  \"configs\": [",
                (unsigned long long)files, (unsigned long long)tokens, (unsigned long long)bytes,
                (unsigned long long)divergences);
        int first = 1;
        for (int c = 0; c < ncfg; c++) {
            if (!active[c]) continue;
            const plab_stats *s = &eng[c].stats;
            fprintf(jo, "%s\n    {\"name\": \"%s\", \"divergences\": %llu, \"coverage_tokens\": %.6f}", first ? "" : ",",
                    cfgs[c].name, (unsigned long long)div[c], s->tokens ? (double)s->committed / s->tokens : 0.0);
            first = 0;
        }
        fprintf(jo, "\n  ]\n}\n");
        fclose(jo);
    }
    return divergences ? 1 : 0;
}
