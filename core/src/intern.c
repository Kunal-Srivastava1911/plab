/* Open-addressing identifier interner with per-run epochs (spec 5.4). */
#include <stdlib.h>
#include <string.h>

#include "plab.h"

static const char *const FIXED[] = {
    "include", "include_next", /* PLAB_ID_INCLUDE, PLAB_ID_INCLUDE_NEXT */
};
static const char *const KEYWORDS[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum",
    "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return",
    "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while", "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic",
    "_Imaginary", "_Noreturn", "_Static_assert", "_Thread_local", "alignas", "alignof", "bool",
    "constexpr", "false", "nullptr", "static_assert", "thread_local", "true", "typeof",
    "typeof_unqual", "_BitInt", "_Decimal32", "_Decimal64", "_Decimal128",
};

static inline uint64_t load_masked(const uint8_t *p, uint32_t n) {
    uint64_t w;
    memcpy(&w, p, 8);
    return n >= 8 ? w : w & ((1ull << (n * 8)) - 1);
}

/* p must be readable for n rounded up to 8 bytes (source buffers carry PLAB_PAD zeros) */
static inline uint32_t hash_padded(const uint8_t *p, uint32_t n) {
    uint64_t h = (uint64_t)n * 0x9E3779B97F4A7C15ull;
    for (uint32_t i = 0; i < n; i += 8) {
        h ^= load_masked(p + i, n - i);
        h *= 0xBF58476D1CE4E5B9ull;
        h ^= h >> 29;
    }
    return (uint32_t)(plab_mix64(h) >> 32);
}

uint32_t plab_hash_spelling(const uint8_t *p, uint32_t n) {
    uint8_t buf[64 + 8] = {0};
    if (n <= 64) {
        memcpy(buf, p, n);
        return hash_padded(buf, n);
    }
    uint8_t *tmp = calloc(n + 8, 1);
    memcpy(tmp, p, n);
    uint32_t h = hash_padded(tmp, n);
    free(tmp);
    return h;
}

int plab_interner_init(plab_interner *in) {
    memset(in, 0, sizeof *in);
    in->mask = (1u << 16) - 1;
    in->slots = calloc(in->mask + 1ull, sizeof in->slots[0]);
    in->cap = 1u << 14;
    in->spell = malloc(in->cap * sizeof in->spell[0]);
    in->slen = malloc(in->cap * sizeof in->slen[0]);
    in->hash = malloc(in->cap * sizeof in->hash[0]);
    in->is_kw = malloc(in->cap);
    return in->slots && in->spell && in->slen && in->hash && in->is_kw ? 0 : -1;
}

void plab_interner_free(plab_interner *in) {
    free(in->slots); free(in->spell); free(in->slen); free(in->hash); free(in->is_kw);
    memset(in, 0, sizeof *in);
}

static void grow_entries(plab_interner *in) {
    in->cap *= 2;
    in->spell = realloc(in->spell, in->cap * sizeof in->spell[0]);
    in->slen = realloc(in->slen, in->cap * sizeof in->slen[0]);
    in->hash = realloc(in->hash, in->cap * sizeof in->hash[0]);
    in->is_kw = realloc(in->is_kw, in->cap);
}

static void grow_slots(plab_interner *in) {
    uint32_t nmask = in->mask * 2 + 1;
    free(in->slots);
    in->slots = calloc(nmask + 1ull, sizeof in->slots[0]);
    in->mask = nmask;
    for (uint32_t id = 0; id < in->count; id++) {
        uint32_t i = in->hash[id] & nmask;
        while (in->slots[i].epoch == in->epoch) i = (i + 1) & nmask;
        in->slots[i].id = id;
        in->slots[i].epoch = in->epoch;
    }
}

static uint32_t intern_hashed(plab_interner *in, const uint8_t *p, uint32_t n, uint32_t h) {
    uint32_t i = h & in->mask;
    for (;;) {
        if (in->slots[i].epoch != in->epoch) break;
        uint32_t id = in->slots[i].id;
        if (in->hash[id] == h && in->slen[id] == n && !memcmp(in->spell[id], p, n)) return id;
        i = (i + 1) & in->mask;
    }
    uint32_t id = in->count++;
    if (id >= in->cap) grow_entries(in);
    in->spell[id] = p;
    in->slen[id] = n;
    in->hash[id] = h;
    in->is_kw[id] = 0;
    in->slots[i].id = id;
    in->slots[i].epoch = in->epoch;
    if (in->count * 2 > in->mask) grow_slots(in);
    return id;
}

uint32_t plab_intern(plab_interner *in, const uint8_t *p, uint32_t n) {
    return intern_hashed(in, p, n, hash_padded(p, n));
}

/* epochs are global so static-table intern caches never alias across engines sharing a table */
static uint32_t global_epoch;

void plab_interner_reset(plab_interner *in) {
    in->epoch = ++global_epoch;
    in->count = 0;
    for (size_t i = 0; i < sizeof FIXED / sizeof FIXED[0]; i++) {
        const uint8_t *s = (const uint8_t *)FIXED[i];
        uint32_t n = (uint32_t)strlen(FIXED[i]);
        intern_hashed(in, s, n, plab_hash_spelling(s, n));
    }
    for (size_t i = 0; i < sizeof KEYWORDS / sizeof KEYWORDS[0]; i++) {
        const uint8_t *s = (const uint8_t *)KEYWORDS[i];
        uint32_t n = (uint32_t)strlen(KEYWORDS[i]);
        in->is_kw[intern_hashed(in, s, n, plab_hash_spelling(s, n))] = 1;
    }
}
