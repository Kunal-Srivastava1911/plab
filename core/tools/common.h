/* Shared helpers for the PLAB command-line tools. */
#ifndef PLAB_TOOLS_COMMON_H
#define PLAB_TOOLS_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plab.h"

#ifdef _WIN32
#include <windows.h>
static inline double now_sec(void) {
    static LARGE_INTEGER f;
    LARGE_INTEGER c;
    if (!f.QuadPart) QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&c);
    return (double)c.QuadPart / (double)f.QuadPart;
}
static inline void pin_thread(void) {
    SetThreadAffinityMask(GetCurrentThread(), 1ull << 2);
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
}
#else
#include <time.h>
static inline double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}
static inline void pin_thread(void) {}
#endif

typedef struct named_config {
    const char *name;
    plab_config cfg;
    int kind_only; /* use the kind-only table */
} named_config;

/* The default configuration and the ablations of spec 8.4. */
static inline int ablation_configs(named_config *out) {
    int n = 0;
    plab_config d = plab_default_config();
    out[n++] = (named_config){"default", d, 0};
    plab_config c;
    /* the predictor exactly as in spec 5.2: order-2 copy table, confidence >= 2, fallback-only training */
    c = d; c.copy_cascade = 0; c.copy_conf_min = 2; c.train_committed = 0;
    out[n++] = (named_config){"spec_predictors", c, 0};
    c = d; c.use_static = 0; out[n++] = (named_config){"copy_only", c, 0};
    c = d; c.use_copy = 0; out[n++] = (named_config){"static_only", c, 0};
    out[n++] = (named_config){"kind_only_contexts", d, 1};
    c = d; c.partial = 0; out[n++] = (named_config){"no_partial", c, 0};
    c = d; c.guard_class = 0; out[n++] = (named_config){"no_guard_classes", c, 0};
    c = d; c.intern_cache = 0; out[n++] = (named_config){"no_intern_cache", c, 0};
    c = d; c.prefetch = 0; out[n++] = (named_config){"no_prefetch", c, 0};
    c = d; c.governor = 0; out[n++] = (named_config){"governor_off", c, 0};
    c = d; c.W = 16; out[n++] = (named_config){"W16", c, 0};
    c = d; c.train_every = 16; out[n++] = (named_config){"train_1_in_16", c, 0};
    return n;
}

typedef struct file_list {
    char **path;
    char **group; /* optional second tab-separated column */
    uint32_t n;
} file_list;

/* one path per line, optionally "group<TAB>path" */
static inline int read_list(const char *fn, file_list *l) {
    FILE *f = fopen(fn, "r");
    if (!f) return -1;
    char line[4096];
    uint32_t cap = 0;
    memset(l, 0, sizeof *l);
    while (fgets(line, sizeof line, f)) {
        line[strcspn(line, "\r\n")] = 0;
        if (!*line) continue;
        if (l->n == cap) {
            cap = cap ? cap * 2 : 256;
            l->path = realloc(l->path, cap * sizeof *l->path);
            l->group = realloc(l->group, cap * sizeof *l->group);
        }
        char *tab = strchr(line, '\t');
        if (tab) { *tab = 0; l->group[l->n] = strdup(line); l->path[l->n] = strdup(tab + 1); }
        else { l->group[l->n] = strdup(""); l->path[l->n] = strdup(line); }
        l->n++;
    }
    fclose(f);
    return 0;
}

/* the "meta" object is produced by scripts/run_all.py and passed through verbatim */
static inline char *read_meta(const char *fn) {
    if (!fn) return strdup("{}");
    uint32_t n;
    uint8_t *b = plab_read_file(fn, &n);
    return b ? (char *)b : strdup("{}");
}

static inline void json_str(FILE *f, const char *s) {
    fputc('"', f);
    for (; *s; s++) {
        unsigned char c = (unsigned char)*s;
        if (c == '"' || c == '\\') fprintf(f, "\\%c", c);
        else if (c < 0x20) fprintf(f, "\\u%04x", c);
        else fputc(c, f);
    }
    fputc('"', f);
}

#endif
