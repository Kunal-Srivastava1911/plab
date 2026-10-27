/* .plabt static table files (spec 5.2): 64-byte header then n2 order-2 and n1 order-1 records. */
#include <stdio.h>
#include <string.h>

#include "plab.h"

typedef struct plabt_header {
    char magic[4];    /* "PLAB" */
    uint16_t version; /* 1 */
    uint8_t lang;     /* 0 = C */
    uint8_t k;        /* maximum lookahead of the token spec */
    uint32_t n2, n1;
    uint32_t flags;
    uint8_t reserved[44];
} plabt_header;
_Static_assert(sizeof(plabt_header) == 64, "header must be 64 bytes");

int plab_table_alloc(plab_table *t, uint32_t n2, uint32_t n1) {
    memset(t, 0, sizeof *t);
    t->n2 = n2;
    t->n1 = n1;
    t->k = 2;
    size_t bytes = ((size_t)n2 + n1 + 1) * sizeof(plab_rec);
    plab_rec *all = plab_aligned_alloc(64, bytes);
    if (!all) return -1;
    memset(all, 0, bytes);
    t->o2 = all;
    t->o1 = all + n2;
    return 0;
}

void plab_table_free(plab_table *t) {
    if (t->o2) plab_aligned_free(t->o2);
    memset(t, 0, sizeof *t);
}

static int is_pow2(uint32_t n) { return n && !(n & (n - 1)); }

int plab_table_load(plab_table *t, const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return -1;
    plabt_header h;
    if (fread(&h, sizeof h, 1, f) != 1 || memcmp(h.magic, "PLAB", 4) || h.version != 1 ||
        (h.n2 && !is_pow2(h.n2)) || (h.n1 && !is_pow2(h.n1)) || plab_table_alloc(t, h.n2, h.n1)) {
        fclose(f);
        return -1;
    }
    t->flags = h.flags;
    t->lang = h.lang;
    t->k = h.k;
    size_t n = (size_t)h.n2 + h.n1;
    int ok = fread(t->o2, sizeof(plab_rec), n, f) == n;
    fclose(f);
    if (!ok) { plab_table_free(t); return -1; }
    for (size_t i = 0; i < n; i++) { t->o2[i].epoch = 0; memset(t->o2[i].intern, 0, sizeof t->o2[i].intern); }
    return 0;
}

int plab_table_save(const plab_table *t, const char *path) {
    FILE *f = fopen(path, "wb");
    if (!f) return -1;
    plabt_header h;
    memset(&h, 0, sizeof h);
    memcpy(h.magic, "PLAB", 4);
    h.version = 1;
    h.lang = t->lang;
    h.k = t->k;
    h.n2 = t->n2;
    h.n1 = t->n1;
    h.flags = t->flags;
    size_t n = (size_t)t->n2 + t->n1;
    int ok = fwrite(&h, sizeof h, 1, f) == 1 && fwrite(t->o2, sizeof(plab_rec), n, f) == n;
    return fclose(f) == 0 && ok ? 0 : -1;
}
