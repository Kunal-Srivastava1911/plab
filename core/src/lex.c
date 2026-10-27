/* Baseline C lexer: hand-written direct-coded maximal munch (the role re2c plays in the spec). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plab.h"

#include "lex_inline.h"

uint8_t plab_cc[256];
#define cc plab_cc

static const struct { const char *s; uint8_t kind; } PUNCTS[] = {
    {"%:%:", TK_DG_HASHHASH}, {"...", TK_ELLIPSIS}, {"<<=", TK_SHL_ASSIGN}, {">>=", TK_SHR_ASSIGN},
    {"->", TK_ARROW}, {"++", TK_INC}, {"--", TK_DEC}, {"<<", TK_SHL}, {">>", TK_SHR},
    {"<=", TK_LE}, {">=", TK_GE}, {"==", TK_EQEQ}, {"!=", TK_NE}, {"&&", TK_ANDAND},
    {"||", TK_OROR}, {"::", TK_COLONCOLON}, {"*=", TK_MUL_ASSIGN}, {"/=", TK_DIV_ASSIGN},
    {"%=", TK_MOD_ASSIGN}, {"+=", TK_ADD_ASSIGN}, {"-=", TK_SUB_ASSIGN}, {"&=", TK_AND_ASSIGN},
    {"|=", TK_OR_ASSIGN}, {"^=", TK_XOR_ASSIGN}, {"##", TK_HASHHASH}, {"<:", TK_DG_LBRACKET},
    {":>", TK_DG_RBRACKET}, {"<%", TK_DG_LBRACE}, {"%>", TK_DG_RBRACE}, {"%:", TK_DG_HASH},
    {"[", TK_LBRACKET}, {"]", TK_RBRACKET}, {"(", TK_LPAREN}, {")", TK_RPAREN}, {"{", TK_LBRACE},
    {"}", TK_RBRACE}, {".", TK_DOT}, {"&", TK_AMP}, {"*", TK_STAR}, {"+", TK_PLUS}, {"-", TK_MINUS},
    {"~", TK_TILDE}, {"!", TK_BANG}, {"/", TK_SLASH}, {"%", TK_PERCENT}, {"<", TK_LT}, {">", TK_GT},
    {"^", TK_CARET}, {"|", TK_PIPE}, {"?", TK_QUESTION}, {":", TK_COLON}, {";", TK_SEMI},
    {"=", TK_ASSIGN}, {",", TK_COMMA}, {"#", TK_HASH},
};
#define NPUNCT (sizeof PUNCTS / sizeof PUNCTS[0])

static const char *NAMES[TK_COUNT] = {
    "none", "identifier", "keyword", "number", "string", "char", "header_name", "pp_end", "unknown",
};

uint64_t plab_extends[TK_COUNT][4];

static void ext_add(int k, uint8_t c) { plab_extends[k][c >> 6] |= 1ull << (c & 63); }
static void ext_str(int k, const char *s) { for (; *s; s++) ext_add(k, (uint8_t)*s); }

const char *plab_kind_name(int kind) { return kind >= 0 && kind < TK_COUNT && NAMES[kind] ? NAMES[kind] : "?"; }

const char *plab_kind_category(int kind) {
    switch (kind) {
    case TK_IDENT: return "identifier";
    case TK_KEYWORD: return "keyword";
    case TK_NUMBER: return "number";
    case TK_STRING: return "string";
    case TK_CHAR: return "char";
    case TK_HEADER_NAME: return "header_name";
    case TK_PP_END: return "pp_end";
    case TK_UNKNOWN: return "unknown";
    default: return "punct";
    }
}

void plab_init(void) {
    static int done;
    if (done) return;
    done = 1;
    for (int c = 0; c < 256; c++) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '$' || c >= 0x80) cc[c] |= C_ID;
        if (c >= '0' && c <= '9') cc[c] |= C_DIGIT | C_ID;
    }
    cc[' '] = cc['\t'] = cc['\v'] = cc['\f'] = cc['\r'] = C_HSPACE;
    for (size_t i = 0; i < NPUNCT; i++) NAMES[PUNCTS[i].kind] = PUNCTS[i].s;
    /* EXTENDS for punctuators: any byte that continues the spelling into a longer punctuator */
    for (size_t i = 0; i < NPUNCT; i++) {
        size_t n = strlen(PUNCTS[i].s);
        for (size_t j = 0; j < NPUNCT; j++)
            if (strlen(PUNCTS[j].s) > n && !strncmp(PUNCTS[j].s, PUNCTS[i].s, n))
                ext_add(PUNCTS[i].kind, (uint8_t)PUNCTS[j].s[n]);
    }
    ext_str(TK_DOT, "0123456789.");
    ext_str(TK_SLASH, "*/");
    for (int c = 0; c < 256; c++)
        if (cc[c] & C_ID) { ext_add(TK_IDENT, (uint8_t)c); ext_add(TK_NUMBER, (uint8_t)c); }
    ext_str(TK_IDENT, "\\\"'");
    ext_str(TK_NUMBER, ".'+-\\");
    memcpy(plab_extends[TK_KEYWORD], plab_extends[TK_IDENT], sizeof plab_extends[0]);
}

uint16_t plab_sigma_after(uint16_t s, int kind, uint32_t id) {
    if (kind == TK_PP_END) return PLAB_S_LINE_START;
    uint16_t out = s & PLAB_S_DIRECTIVE;
    if ((kind == TK_HASH || kind == TK_DG_HASH) && (s & PLAB_S_LINE_START) && !(s & PLAB_S_DIRECTIVE))
        out |= PLAB_S_DIRECTIVE | PLAB_S_DNAME;
    else if (kind == TK_IDENT && (s & PLAB_S_DNAME) && (id == PLAB_ID_INCLUDE || id == PLAB_ID_INCLUDE_NEXT))
        out |= PLAB_S_INCLUDE;
    return out;
}

int plab_lex_one(const plab_lexer *L, uint32_t *pp, uint16_t *sigma, plab_tokens *t) {
    return lex_one_inline(L, pp, sigma, t);
}

/* The baseline loop. Not inlined, so the baseline alone and PLAB's baseline windows run the
 * same machine code. */
__attribute__((noinline)) uint32_t plab_lex_until(const plab_lexer *L, uint32_t p, uint16_t *sigma,
                                                  plab_tokens *t, uint32_t end) {
    uint16_t sig = *sigma;
    while (p < end)
        if (!lex_one_inline(L, &p, &sig, t)) break;
    *sigma = sig;
    return p;
}

void plab_lex_all(const plab_lexer *L, plab_tokens *t) {
    uint16_t sig = PLAB_S_LINE_START;
    plab_lex_until(L, 0, &sig, t, L->len);
}

int plab_tokens_init(plab_tokens *t, uint32_t source_len) {
    /* every token is at least one byte, so source_len + 64 never overflows (the spec's len/2 can) */
    uint32_t cap = source_len + 64;
    t->kind = malloc(cap);
    t->start = malloc(cap * 4ull);
    t->len = malloc(cap * 4ull);
    t->id = malloc(cap * 4ull);
    t->sigma = malloc(cap * 2ull);
    t->count = 0;
    t->capacity = cap;
    t->lines = 0;
    return t->kind && t->start && t->len && t->id && t->sigma ? 0 : -1;
}

void plab_tokens_free(plab_tokens *t) {
    free(t->kind); free(t->start); free(t->len); free(t->id); free(t->sigma);
    memset(t, 0, sizeof *t);
}

uint8_t *plab_read_file(const char *path, uint32_t *len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (n < 0 || n > 0x7FFFFFFFL - PLAB_PAD) { fclose(f); return NULL; }
    uint8_t *buf = calloc((size_t)n + PLAB_PAD, 1);
    if (buf && fread(buf, 1, (size_t)n, f) != (size_t)n) { free(buf); buf = NULL; }
    fclose(f);
    if (buf) *len = (uint32_t)n;
    return buf;
}

void *plab_aligned_alloc(size_t align, size_t size) {
#ifdef _WIN32
    return _aligned_malloc(size, align);
#else
    void *p = NULL;
    return posix_memalign(&p, align, size) ? NULL : p;
#endif
}

void plab_aligned_free(void *p) {
#ifdef _WIN32
    _aligned_free(p);
#else
    free(p);
#endif
}
