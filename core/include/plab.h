/* PLAB: Predictive Lexical Analysis Buffering. Public API (spec sections 3-6). */
#ifndef PLAB_H
#define PLAB_H

#include <stddef.h>
#include <stdint.h>

#define PLAB_PAD 64      /* zero bytes required after the end of every source buffer */
#define PLAB_W 32        /* phrase window in bytes */
#define PLAB_MAXTOK 8    /* tokens per phrase */
#ifndef PLAB_COPY_N
#define PLAB_COPY_N 4096 /* copy predictor entries (8 bytes each) */
#endif
#define PLAB_RING 64     /* training ring */
#define PLAB_WINDOW 4096 /* governor window in bytes */

/* ---- token kinds ---- */
enum plab_kind {
    TK_NONE = 0,
    TK_IDENT, TK_KEYWORD, TK_NUMBER, TK_STRING, TK_CHAR, TK_HEADER_NAME, TK_PP_END, TK_UNKNOWN,
    TK_LBRACKET, TK_RBRACKET, TK_LPAREN, TK_RPAREN, TK_LBRACE, TK_RBRACE,
    TK_DOT, TK_ARROW, TK_INC, TK_DEC, TK_AMP, TK_STAR, TK_PLUS, TK_MINUS, TK_TILDE, TK_BANG,
    TK_SLASH, TK_PERCENT, TK_SHL, TK_SHR, TK_LT, TK_GT, TK_LE, TK_GE, TK_EQEQ, TK_NE,
    TK_CARET, TK_PIPE, TK_ANDAND, TK_OROR, TK_QUESTION, TK_COLON, TK_COLONCOLON, TK_SEMI,
    TK_ELLIPSIS, TK_ASSIGN, TK_MUL_ASSIGN, TK_DIV_ASSIGN, TK_MOD_ASSIGN, TK_ADD_ASSIGN,
    TK_SUB_ASSIGN, TK_SHL_ASSIGN, TK_SHR_ASSIGN, TK_AND_ASSIGN, TK_OR_ASSIGN, TK_XOR_ASSIGN,
    TK_COMMA, TK_HASH, TK_HASHHASH,
    TK_DG_LBRACKET, TK_DG_RBRACKET, TK_DG_LBRACE, TK_DG_RBRACE, TK_DG_HASH, TK_DG_HASHHASH,
    TK_COUNT
};

const char *plab_kind_name(int kind);
const char *plab_kind_category(int kind); /* "keyword", "identifier", "number", "punct", ... */

/* ---- lexer state signature sigma (section 4) ---- */
#define PLAB_S_LINE_START 1u /* only whitespace since the last newline */
#define PLAB_S_DIRECTIVE 2u  /* inside a preprocessor line */
#define PLAB_S_INCLUDE 4u    /* after #include / #include_next: <...> is a header-name */
#define PLAB_S_DNAME 8u      /* right after the directive-introducing #: next token is the name */

/* EXTENDS[kind]: 256-bit set of bytes that could extend a token of that kind (section 3) */
extern uint64_t plab_extends[TK_COUNT][4];
static inline int plab_extends_has(int kind, uint8_t c) {
    return (int)((plab_extends[kind][c >> 6] >> (c & 63)) & 1);
}
void plab_init(void); /* builds EXTENDS; call once */

/* ---- phrase record (5.1) ---- */
typedef struct plab_rec {
    uint16_t tag;
    uint16_t sigma_in;
    uint8_t len;      /* L, 1..32 */
    uint8_t ntok;     /* 1..8 */
    uint8_t conf;     /* initial confidence (static tables) */
    uint8_t newlines; /* newlines in bytes[0, len) */
    uint8_t bytes[32];
    uint32_t ends;     /* bit i set if a token ends at offset i + 1 */
    uint16_t desc[8];  /* (end_offset << 10) | kind */
    uint32_t intern[8];
    uint32_t epoch;
    uint32_t next_ctx;
    uint16_t sigma_out;
    uint8_t source;   /* 0 static order-1, 1 static order-2, 2 copy */
    /* pad[25] of the spec, used for per-token data needed by partial commits: */
    uint8_t start_off[8]; /* token start offset (after leading trivia) */
    uint8_t sig_tok[8];   /* low nibble: sigma at token start, high nibble: sigma after token */
    uint8_t pad0;
    uint32_t nlmask;      /* bit i set if bytes[i] == '\n' */
    uint8_t pad[4];
} plab_rec;
_Static_assert(sizeof(plab_rec) == 128, "record must be 128 bytes");

enum { PLAB_SRC_O1 = 0, PLAB_SRC_O2 = 1, PLAB_SRC_COPY = 2 };

/* ---- token buffer (5.3) ---- */
typedef struct plab_tokens {
    uint8_t *kind;
    uint32_t *start;
    uint32_t *len;
    uint32_t *id;     /* intern ID for identifiers and keywords, else 0 */
    uint16_t *sigma;  /* state at the token's first byte */
    uint32_t count, capacity;
    uint32_t lines;
} plab_tokens;

int plab_tokens_init(plab_tokens *t, uint32_t source_len);
void plab_tokens_free(plab_tokens *t);

/* ---- interner (5.4) ---- */
typedef struct plab_interner {
    struct { uint32_t id, epoch; } *slots;
    uint32_t mask;
    const uint8_t **spell;
    uint32_t *slen;
    uint32_t *hash; /* stable spelling hash: the context identity of an identifier */
    uint8_t *is_kw;
    uint32_t count, cap;
    uint32_t epoch;
} plab_interner;

enum { PLAB_ID_INCLUDE = 0, PLAB_ID_INCLUDE_NEXT = 1 }; /* pre-interned before keywords */

int plab_interner_init(plab_interner *in);
void plab_interner_free(plab_interner *in);
void plab_interner_reset(plab_interner *in); /* new run: epoch++, pre-intern fixed spellings */
uint32_t plab_intern(plab_interner *in, const uint8_t *p, uint32_t n); /* p must be padded */
uint32_t plab_hash_spelling(const uint8_t *p, uint32_t n);

/* ---- baseline lexer ---- */
typedef struct plab_lexer {
    const uint8_t *src;
    uint32_t len;
    plab_interner *in;
} plab_lexer;

/* Lex leading trivia and one token at *p. Returns 1 if a token was appended, 0 at end. */
int plab_lex_one(const plab_lexer *L, uint32_t *p, uint16_t *sigma, plab_tokens *t);
void plab_lex_all(const plab_lexer *L, plab_tokens *t); /* the baseline alone */
/* lex tokens from p while p < end; returns the new position */
uint32_t plab_lex_until(const plab_lexer *L, uint32_t p, uint16_t *sigma, plab_tokens *t, uint32_t end);
uint16_t plab_sigma_after(uint16_t s, int kind, uint32_t id);

/* ---- static tables (.plabt) ---- */
typedef struct plab_table {
    plab_rec *o2, *o1;
    uint32_t n2, n1;
    uint32_t flags; /* bit 0: kind-only contexts */
    uint8_t lang, k;
} plab_table;

#define PLAB_TABLE_KIND_ONLY 1u
int plab_table_load(plab_table *t, const char *path);
int plab_table_save(const plab_table *t, const char *path);
int plab_table_alloc(plab_table *t, uint32_t n2, uint32_t n1);
void plab_table_free(plab_table *t);

/* ---- context hash (5.2) ---- */
#define PLAB_P1 0x9E3779B97F4A7C15ull
#define PLAB_P2 0xC2B2AE3D27D4EB4Full
#define PLAB_SALT1 0x5BD1E9955BD1E995ull
static inline uint64_t plab_mix64(uint64_t z) {
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
    return z ^ (z >> 31);
}
static inline uint64_t plab_ctx2(uint32_t c2, uint32_t c1, uint32_t s) {
    return plab_mix64((uint64_t)c2 * PLAB_P1 ^ (uint64_t)c1 * PLAB_P2 ^ s);
}
#define PLAB_P3 0x165667B19E3779F9ull
static inline uint64_t plab_ctx3(uint32_t c3, uint32_t c2, uint32_t c1, uint32_t s) {
    return plab_mix64((uint64_t)c3 * PLAB_P3 ^ (uint64_t)c2 * PLAB_P1 ^ (uint64_t)c1 * PLAB_P2 ^ s);
}
static inline uint64_t plab_ctx1(uint32_t c1, uint32_t s) {
    return plab_mix64((uint64_t)c1 * PLAB_P2 ^ s ^ PLAB_SALT1);
}
static inline uint16_t plab_tag(uint64_t h) { return (uint16_t)(h >> 48); }

/* context identity of token i: spelling hash for identifiers/keywords, else the kind */
static inline uint32_t plab_cid(const plab_tokens *t, const plab_interner *in, uint32_t i, int kind_only) {
    uint8_t k = t->kind[i];
    return (!kind_only && (k == TK_IDENT || k == TK_KEYWORD)) ? in->hash[t->id[i]] : k;
}

/* Fill r with the phrase that follows token `i` (i == UINT32_MAX: start of file) using tokens
 * up to index `last`. Returns ntok (0 if no recordable phrase). Shared by copy drafts and mining. */
int plab_make_record(plab_rec *r, const uint8_t *src, const plab_tokens *t, uint32_t i,
                     uint32_t last, uint32_t W, uint16_t sigma_in);

/* ---- engine ---- */
typedef struct plab_config {
    uint8_t use_copy, use_static;
    uint8_t partial;      /* partial acceptance */
    uint8_t guard_class;  /* EXTENDS guard (else exact recorded guard bytes) */
    uint8_t intern_cache; /* reuse cached intern IDs */
    uint8_t prefetch;
    uint8_t governor;
    uint8_t W;            /* 16 or 32 */
    uint8_t copy_cascade; /* copy tables for context orders 3, 2, 1 (else order 2 only, as in 5.2) */
    uint8_t copy_conf_min;/* copy confidence needed to probe (spec: 2) */
    uint8_t train_committed; /* also train the copy predictor inside committed phrases */
    uint8_t train_every;  /* train the copy predictor at 1 in this many positions (power of two) */
} plab_config;

plab_config plab_default_config(void);

typedef struct plab_stats {
    uint64_t tokens, committed, phrases, partial, probes, failed;
    uint64_t by_source[3];
    uint64_t hist[8];
    uint64_t windows_spec, windows_base;
} plab_stats;

/* per-token trace for the token inspector (section 9.3) */
enum { PLAB_O_FALLBACK = 0, PLAB_O_COMMIT, PLAB_O_PARTIAL, PLAB_O_MISS };
typedef struct plab_trace_phrase {
    uint32_t s, e;            /* byte range of the predicted phrase */
    uint8_t ntok, accepted, src, conf;
    int32_t mismatch_at;      /* -1 if none */
    uint8_t expected, actual;
} plab_trace_phrase;
typedef struct plab_trace {
    uint8_t *outcome;  /* per token */
    int32_t *phrase;   /* per token, -1 = none */
    uint8_t *conf;     /* per token */
    plab_trace_phrase *phrases;
    uint32_t nphrases, cap;
} plab_trace;

/* cs: 2-bit confidence | sigma << 4. fp: 8-bit fingerprint of the token that followed tok_index,
 * so training never reads old tokens. */
typedef struct plab_copy_ent { uint16_t tag; uint8_t cs; uint8_t fp; uint32_t tok_index; } plab_copy_ent;

typedef struct plab_engine {
    plab_rec scratch;           /* materialized copy draft; 128 B, kept first for alignment */
    const plab_table *tab;
    plab_config cfg;
    plab_interner in;
    plab_copy_ent copy[PLAB_COPY_N];
    uint8_t *sconf2, *sconf1;   /* per-run confidence of static records */
    uint8_t *iconf;             /* initial confidences (n2 then n1), copied in at each run */
    uint32_t *key2, *key1;      /* compact probe keys: valid << 31 | sigma_in << 16 | tag (L1-resident) */
    struct { uint64_t h; uint32_t ti; uint8_t lvl, sig; } ring[PLAB_RING];
    uint32_t ring_n;
    uint32_t train_ctr;
    int pred_dirty;            /* predictor state not yet reset for this run */
    double gov_cyc[2], gov_bytes[2]; /* governor: decayed cycles and bytes for baseline [0] / PLAB [1] */
    uint64_t gov_windows, gov_next, gov_interval;
    int gov_pref;
    int kind_only;
    plab_stats stats;
    plab_trace *trace;
} plab_engine;

int plab_engine_init(plab_engine *e, const plab_table *tab, plab_config cfg);
void plab_engine_free(plab_engine *e);
/* Lex src[0, len) (padded) into t with PLAB. t must be initialised for len. */
void plab_run(plab_engine *e, const uint8_t *src, uint32_t len, plab_tokens *t);
/* The baseline alone with the same interner semantics (for comparisons). */
void plab_run_baseline(plab_interner *in, const uint8_t *src, uint32_t len, plab_tokens *t);

/* ---- utilities ---- */
uint8_t *plab_read_file(const char *path, uint32_t *len); /* padded with PLAB_PAD zeros */
void *plab_aligned_alloc(size_t align, size_t size);
void plab_aligned_free(void *p);

#endif
