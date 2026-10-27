/* plab_trace: per-token PLAB outcomes for the token inspector (spec 9.3).
 *
 *   plab_trace --table c.plabt --list traces.txt --out-dir web/public/traces [--meta meta.json]
 *
 * traces.txt lines are "name<TAB>display path<TAB>file path". Writes <name>.json per file and
 * index.json. Source text keeps byte offsets: invalid UTF-8 bytes are replaced by '?'. */
#include "common.h"

static const char *SRC_NAMES[3] = {"static_o1", "static_o2", "copy"};
static const char *OUTCOMES[4] = {"fallback", "commit", "partial", "miss"};

/* length of a valid UTF-8 sequence at s (0 if invalid) */
static int utf8_len(const uint8_t *s, uint32_t left) {
    uint8_t c = s[0];
    int n = c < 0x80 ? 1 : (c >> 5) == 6 ? 2 : (c >> 4) == 14 ? 3 : (c >> 3) == 30 ? 4 : 0;
    if (!n || (uint32_t)n > left) return 0;
    for (int i = 1; i < n; i++) if ((s[i] & 0xC0) != 0x80) return 0;
    if (n == 2 && c < 0xC2) return 0;
    return n;
}

static void json_source(FILE *f, const uint8_t *s, uint32_t len) {
    fputc('"', f);
    for (uint32_t i = 0; i < len;) {
        uint8_t c = s[i];
        if (c >= 0x80) {
            int n = utf8_len(s + i, len - i);
            if (n) { fwrite(s + i, 1, (size_t)n, f); i += (uint32_t)n; }
            else { fputc('?', f); i++; }
            continue;
        }
        if (c == '"' || c == '\\') fprintf(f, "\\%c", c);
        else if (c == '\n') fputs("\\n", f);
        else if (c == '\t') fputs("\\t", f);
        else if (c == '\r') fputs("\\r", f);
        else if (c < 0x20) fprintf(f, "\\u%04x", c);
        else fputc(c, f);
        i++;
    }
    fputc('"', f);
}

int main(int argc, char **argv) {
    const char *tpath = NULL, *list = NULL, *outdir = NULL, *meta = NULL;
    for (int a = 1; a < argc; a++) {
        if (!strcmp(argv[a], "--table") && a + 1 < argc) tpath = argv[++a];
        else if (!strcmp(argv[a], "--list") && a + 1 < argc) list = argv[++a];
        else if (!strcmp(argv[a], "--out-dir") && a + 1 < argc) outdir = argv[++a];
        else if (!strcmp(argv[a], "--meta") && a + 1 < argc) meta = argv[++a];
        else { fprintf(stderr, "unknown argument %s\n", argv[a]); return 2; }
    }
    if (!tpath || !list || !outdir) { fprintf(stderr, "usage: plab_trace --table T --list L --out-dir D\n"); return 2; }
    plab_init();
    plab_table tab;
    if (plab_table_load(&tab, tpath)) { fprintf(stderr, "cannot load %s\n", tpath); return 2; }
    char *metas = read_meta(meta);
    FILE *lf = fopen(list, "r");
    if (!lf) { perror(list); return 2; }
    char path[4096];
    snprintf(path, sizeof path, "%s/index.json", outdir);
    FILE *idx = fopen(path, "w");
    if (!idx) { perror(path); return 2; }
    fprintf(idx, "{ \"files\": [");
    int first_file = 1;
    char line[8192];
    while (fgets(line, sizeof line, lf)) {
        line[strcspn(line, "\r\n")] = 0;
        char *name = line, *disp = strchr(name, '\t'), *file;
        if (!disp) continue;
        *disp++ = 0;
        file = strchr(disp, '\t');
        if (!file) continue;
        *file++ = 0;
        uint32_t len;
        uint8_t *src = plab_read_file(file, &len);
        if (!src) { fprintf(stderr, "cannot read %s\n", file); continue; }

        plab_engine e;
        plab_engine_init(&e, &tab, plab_default_config());
        plab_trace tr = {0};
        tr.outcome = calloc(len + 64, 1);
        tr.phrase = calloc(len + 64, sizeof(int32_t));
        tr.conf = calloc(len + 64, 1);
        e.trace = &tr;
        plab_tokens t;
        plab_tokens_init(&t, len);
        plab_run(&e, src, len, &t);
        double cov = t.count ? (double)e.stats.committed / t.count : 0.0;

        snprintf(path, sizeof path, "%s/%s.json", outdir, name);
        FILE *f = fopen(path, "w");
        if (!f) { perror(path); return 2; }
        fprintf(f, "{\"meta\": %s, \"name\": ", metas);
        json_str(f, name);
        fprintf(f, ", \"path\": ");
        json_str(f, disp);
        fprintf(f, ", \"source\": ");
        json_source(f, src, len);
        fprintf(f, ",\n\"tokens\": [");
        for (uint32_t i = 0; i < t.count; i++) {
            int32_t ph = tr.phrase[i];
            fprintf(f, "%s\n{\"s\":%u,\"e\":%u,\"k\":\"%s\",\"o\":\"%s\",\"ph\":", i ? "," : "", t.start[i],
                    t.start[i] + t.len[i], plab_kind_name(t.kind[i]), OUTCOMES[tr.outcome[i]]);
            if (ph >= 0) fprintf(f, "%d,\"src\":\"%s\",\"conf\":%u}", ph, SRC_NAMES[tr.phrases[ph].src], tr.phrases[ph].conf);
            else fprintf(f, "null,\"src\":null,\"conf\":null}");
        }
        fprintf(f, "],\n\"phrases\": [");
        for (uint32_t i = 0; i < tr.nphrases; i++) {
            const plab_trace_phrase *p = &tr.phrases[i];
            fprintf(f, "%s\n{\"id\":%u,\"s\":%u,\"e\":%u,\"ntok\":%u,\"accepted\":%u,\"src\":\"%s\",\"conf\":%u,\"mismatch_at\":",
                    i ? "," : "", i, p->s, p->e, p->ntok, p->accepted, SRC_NAMES[p->src], p->conf);
            if (p->mismatch_at >= 0 && !p->accepted)
                fprintf(f, "%d,\"expected\":%u,\"actual\":%u}", p->mismatch_at, p->expected, p->actual);
            else if (p->mismatch_at >= 0)
                fprintf(f, "%d,\"expected\":null,\"actual\":null}", p->mismatch_at);
            else
                fprintf(f, "null,\"expected\":null,\"actual\":null}");
        }
        fprintf(f, "]}\n");
        fclose(f);

        fprintf(idx, "%s\n  {\"name\": ", first_file ? "" : ",");
        json_str(idx, name);
        fprintf(idx, ", \"path\": ");
        json_str(idx, disp);
        fprintf(idx, ", \"bytes\": %u, \"tokens\": %u, \"coverage\": %.4f}", len, t.count, cov);
        first_file = 0;
        fprintf(stderr, "%-28s %7u bytes %6u tokens coverage %.3f phrases %u\n", name, len, t.count, cov, tr.nphrases);

        plab_tokens_free(&t);
        plab_engine_free(&e);
        free(tr.outcome); free(tr.phrase); free(tr.conf); free(tr.phrases);
        free(src);
    }
    fprintf(idx, "\n] }\n");
    fclose(idx);
    fclose(lf);
    return 0;
}
