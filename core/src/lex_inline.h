/* The baseline lexer body, inlined into both the baseline loop and the PLAB fallback path. */
#ifndef PLAB_LEX_INLINE_H
#define PLAB_LEX_INLINE_H

#include "plab.h"

enum { C_ID = 1, C_DIGIT = 2, C_HSPACE = 4 };
extern uint8_t plab_cc[256];
#define cc plab_cc

/* scan a "..." or '...' literal starting at q (the quote). Returns end, or 0 if unterminated. */
static inline uint32_t scan_quoted(const uint8_t *s, uint32_t q, uint32_t len, uint8_t quote, uint32_t *nl) {
    uint32_t i = q + 1;
    while (i < len) {
        uint8_t c = s[i];
        if (c == quote) return i + 1;
        if (c == '\n') return 0;
        if (c == '\\') {
            if (s[i + 1] == '\n') { (*nl)++; i += 2; continue; }
            if (s[i + 1] == '\r' && s[i + 2] == '\n') { (*nl)++; i += 3; continue; }
            i += 2;
            continue;
        }
        i++;
    }
    return 0;
}

static inline void emit(plab_tokens *t, uint8_t kind, uint32_t start, uint32_t len, uint32_t id, uint16_t sig) {
    uint32_t c = t->count++;
    t->kind[c] = kind;
    t->start[c] = start;
    t->len[c] = len;
    t->id[c] = id;
    t->sigma[c] = sig;
}

static inline __attribute__((always_inline)) int lex_one_inline(const plab_lexer *L, uint32_t *pp, uint16_t *sigma, plab_tokens *t) {
    const uint8_t *s = L->src;
    const uint32_t len = L->len;
    uint32_t p = *pp;
    uint16_t sig = *sigma;

    /* ---- trivia ---- */
    for (;;) {
        uint8_t c = s[p];
        if (cc[c] & C_HSPACE) { p++; continue; }
        if (c == '\n') {
            if (p >= len) break;
            if (sig & PLAB_S_DIRECTIVE) {
                emit(t, TK_PP_END, p, 1, 0, sig);
                t->lines++;
                *pp = p + 1;
                *sigma = PLAB_S_LINE_START;
                return 1;
            }
            t->lines++;
            sig |= PLAB_S_LINE_START;
            p++;
            continue;
        }
        if (c == '/') {
            if (s[p + 1] == '/') {
                p += 2;
                while (p < len && s[p] != '\n') p++;
                continue;
            }
            if (s[p + 1] == '*') {
                p += 2;
                for (;;) {
                    if (p >= len) { p = len; break; }
                    if (s[p] == '*' && s[p + 1] == '/') { p += 2; break; }
                    if (s[p] == '\n') t->lines++;
                    p++;
                }
                continue;
            }
            break;
        }
        if (c == '\\') {
            if (s[p + 1] == '\n') { t->lines++; p += 2; continue; }
            if (s[p + 1] == '\r' && s[p + 2] == '\n') { t->lines++; p += 3; continue; }
        }
        break;
    }
    if (p >= len) { *pp = len; *sigma = sig; return 0; }

    /* ---- one token ---- */
    const uint32_t start = p;
    uint8_t c = s[p];
    uint8_t kind;
    uint32_t id = 0, end;

    if ((sig & PLAB_S_INCLUDE) && (c == '<' || c == '"')) {
        uint8_t close = c == '<' ? '>' : '"';
        uint32_t i = p + 1;
        while (i < len && s[i] != close && s[i] != '\n') i++;
        if (i < len && s[i] == close) { kind = TK_HEADER_NAME; end = i + 1; goto done; }
    }

    if ((cc[c] & (C_ID | C_DIGIT)) == C_ID) {
        uint32_t i = p + 1;
        while (cc[s[i]] & C_ID) i++;
        uint32_t n = i - p;
        uint8_t q = s[i];
        if ((q == '"' || q == '\'') &&
            ((n == 1 && (c == 'L' || c == 'u' || c == 'U')) || (n == 2 && c == 'u' && s[p + 1] == '8'))) {
            uint32_t nl = 0, e = scan_quoted(s, i, len, q, &nl);
            if (e) { kind = q == '"' ? TK_STRING : TK_CHAR; end = e; t->lines += nl; goto done; }
        }
        id = plab_intern(L->in, s + p, n);
        kind = L->in->is_kw[id] ? TK_KEYWORD : TK_IDENT;
        end = i;
        goto done;
    }
    if ((cc[c] & C_DIGIT) || (c == '.' && (cc[s[p + 1]] & C_DIGIT))) {
        uint32_t i = p + 1;
        for (;;) {
            uint8_t d = s[i];
            if ((cc[d] & C_ID) || d == '.') { i++; continue; }
            if ((d == '+' || d == '-') && (s[i - 1] | 0x20) == 'e') { i++; continue; }
            if ((d == '+' || d == '-') && (s[i - 1] | 0x20) == 'p') { i++; continue; }
            if (d == '\'' && (cc[s[i + 1]] & C_ID)) { i += 2; continue; }
            break;
        }
        kind = TK_NUMBER;
        end = i;
        goto done;
    }
    if (c == '"' || c == '\'') {
        uint32_t nl = 0, e = scan_quoted(s, p, len, c, &nl);
        if (e) { kind = c == '"' ? TK_STRING : TK_CHAR; end = e; t->lines += nl; }
        else { kind = TK_UNKNOWN; end = p + 1; }
        goto done;
    }

    {
        uint8_t c1 = s[p + 1], c2 = s[p + 2];
        end = p + 1;
        switch (c) {
        case '[': kind = TK_LBRACKET; break;
        case ']': kind = TK_RBRACKET; break;
        case '(': kind = TK_LPAREN; break;
        case ')': kind = TK_RPAREN; break;
        case '{': kind = TK_LBRACE; break;
        case '}': kind = TK_RBRACE; break;
        case '~': kind = TK_TILDE; break;
        case '?': kind = TK_QUESTION; break;
        case ';': kind = TK_SEMI; break;
        case ',': kind = TK_COMMA; break;
        case '.':
            if (c1 == '.' && c2 == '.') { kind = TK_ELLIPSIS; end = p + 3; }
            else kind = TK_DOT;
            break;
        case '-':
            if (c1 == '>') { kind = TK_ARROW; end++; }
            else if (c1 == '-') { kind = TK_DEC; end++; }
            else if (c1 == '=') { kind = TK_SUB_ASSIGN; end++; }
            else kind = TK_MINUS;
            break;
        case '+':
            if (c1 == '+') { kind = TK_INC; end++; }
            else if (c1 == '=') { kind = TK_ADD_ASSIGN; end++; }
            else kind = TK_PLUS;
            break;
        case '&':
            if (c1 == '&') { kind = TK_ANDAND; end++; }
            else if (c1 == '=') { kind = TK_AND_ASSIGN; end++; }
            else kind = TK_AMP;
            break;
        case '|':
            if (c1 == '|') { kind = TK_OROR; end++; }
            else if (c1 == '=') { kind = TK_OR_ASSIGN; end++; }
            else kind = TK_PIPE;
            break;
        case '*': if (c1 == '=') { kind = TK_MUL_ASSIGN; end++; } else kind = TK_STAR; break;
        case '/': if (c1 == '=') { kind = TK_DIV_ASSIGN; end++; } else kind = TK_SLASH; break;
        case '^': if (c1 == '=') { kind = TK_XOR_ASSIGN; end++; } else kind = TK_CARET; break;
        case '!': if (c1 == '=') { kind = TK_NE; end++; } else kind = TK_BANG; break;
        case '=': if (c1 == '=') { kind = TK_EQEQ; end++; } else kind = TK_ASSIGN; break;
        case '#': if (c1 == '#') { kind = TK_HASHHASH; end++; } else kind = TK_HASH; break;
        case ':':
            if (c1 == ':') { kind = TK_COLONCOLON; end++; }
            else if (c1 == '>') { kind = TK_DG_RBRACKET; end++; }
            else kind = TK_COLON;
            break;
        case '<':
            if (c1 == '<') {
                if (c2 == '=') { kind = TK_SHL_ASSIGN; end += 2; } else { kind = TK_SHL; end++; }
            } else if (c1 == '=') { kind = TK_LE; end++; }
            else if (c1 == ':') { kind = TK_DG_LBRACKET; end++; }
            else if (c1 == '%') { kind = TK_DG_LBRACE; end++; }
            else kind = TK_LT;
            break;
        case '>':
            if (c1 == '>') {
                if (c2 == '=') { kind = TK_SHR_ASSIGN; end += 2; } else { kind = TK_SHR; end++; }
            } else if (c1 == '=') { kind = TK_GE; end++; }
            else kind = TK_GT;
            break;
        case '%':
            if (c1 == ':') {
                if (c2 == '%' && s[p + 3] == ':') { kind = TK_DG_HASHHASH; end += 3; }
                else { kind = TK_DG_HASH; end++; }
            } else if (c1 == '=') { kind = TK_MOD_ASSIGN; end++; }
            else if (c1 == '>') { kind = TK_DG_RBRACE; end++; }
            else kind = TK_PERCENT;
            break;
        default: kind = TK_UNKNOWN; break;
        }
    }

done:
    if (end > len) end = len;
    emit(t, kind, start, end - start, id, sig);
    *sigma = plab_sigma_after(sig, kind, id);
    *pp = end;
    return 1;
}

#undef cc

#endif
