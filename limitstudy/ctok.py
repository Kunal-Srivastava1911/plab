"""Regex maximal-munch C tokenizer for the Phase 0 limit study (spec 8.1).

Tokens are (kind, start, end, text, sigma): `start`/`end` are byte offsets of the
token text, `sigma` is the lexer state at the token's first byte (spec section 4).
Whitespace and comments are trivia: they belong to the next token as leading bytes
(the bytes between the previous token's end and this token's start).
"""
import re

# sigma bits (spec section 4; bit 3 is the directive-name bit, see DESIGN_NOTES.md)
S_LINE_START = 1
S_DIRECTIVE = 2
S_INCLUDE = 4
S_DNAME = 8

KEYWORDS = set(b"""auto break case char const continue default do double else enum extern
float for goto if inline int long register restrict return short signed sizeof static
struct switch typedef union unsigned void volatile while _Alignas _Alignof _Atomic _Bool
_Complex _Generic _Imaginary _Noreturn _Static_assert _Thread_local alignas alignof bool
constexpr false nullptr static_assert thread_local true typeof typeof_unqual _BitInt
_Decimal32 _Decimal64 _Decimal128""".split())

PUNCTS = sorted(b"""[ ] ( ) { } . -> ++ -- & * + - ~ ! / % << >> < > <= >= == != ^ | && ||
? : :: ; ... = *= /= %= += -= <<= >>= &= |= ^= , # ## <: :> <% %> %: %:%:""".split(),
                key=len, reverse=True)

KIND_NAMES = ["ident", "keyword", "number", "string", "char", "header_name", "pp_end",
              "unknown"] + [p.decode() for p in sorted(PUNCTS)]
KIND_ID = {k: i + 1 for i, k in enumerate(KIND_NAMES)}
NEVER_RECORD = {"header_name", "unknown"}


def _set(s):
    return frozenset(s.encode() if isinstance(s, str) else s)


_IDCHARS = _set("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_$") | frozenset(range(0x80, 0x100))


def _build_extends():
    ext = {}
    for p in PUNCTS:
        ext[p.decode()] = frozenset(q[len(p)] for q in PUNCTS if len(q) > len(p) and q.startswith(p))
    ext["."] |= _set("0123456789.")
    ext["/"] |= _set("*/")
    ext["ident"] = _IDCHARS | _set("\\\"'")
    ext["keyword"] = ext["ident"]
    ext["number"] = _IDCHARS | _set(".'+-\\")
    for k in ("string", "char", "header_name", "pp_end", "unknown"):
        ext[k] = frozenset()
    return ext


# EXTENDS[kind]: bytes that could extend a token of that kind (never under-approximates)
EXTENDS = _build_extends()

_TRIVIA = re.compile(rb"(?:[ \t\v\f\r]+|//[^\n]*|/\*.*?(?:\*/|\Z)|\\\r?\n)+", re.S)
_ID = re.compile(rb"[A-Za-z_$\x80-\xff][A-Za-z0-9_$\x80-\xff]*")
_NUM = re.compile(rb"\.?[0-9](?:[eEpP][+-]|'[A-Za-z0-9_$\x80-\xff]|[A-Za-z0-9_$\x80-\xff.])*")
_STR = re.compile(rb'"(?:[^"\\\n]|\\(?:\r?\n|.))*"', re.S)
_CHR = re.compile(rb"'(?:[^'\\\n]|\\(?:\r?\n|.))*'", re.S)
_HDR_ANGLE = re.compile(rb"<[^>\n]*>")
_HDR_QUOTE = re.compile(rb'"[^"\n]*"')
_PUNCT = re.compile(b"|".join(re.escape(p) for p in PUNCTS))
_PREFIX = (b"L", b"u", b"U", b"u8")


def sigma_after(s, kind, text):
    """State right after a token that started in state s (mirrors core/src/lex.c)."""
    if kind == "pp_end":
        return S_LINE_START
    out = s & S_DIRECTIVE
    if kind in ("#", "%:") and (s & S_LINE_START) and not (s & S_DIRECTIVE):
        out |= S_DIRECTIVE | S_DNAME
    elif kind == "ident" and (s & S_DNAME) and text in (b"include", b"include_next"):
        out |= S_INCLUDE
    return out


def tokenize(src: bytes):
    """Yield (kind, start, end, text, sigma) for a C source buffer."""
    toks = []
    n = len(src)
    p = 0
    s = S_LINE_START
    while True:
        # trivia
        while p < n:
            m = _TRIVIA.match(src, p)
            if m:
                p = m.end()
            if p < n and src[p] == 0x0A:
                if s & S_DIRECTIVE:
                    break
                s |= S_LINE_START
                p += 1
                continue
            break
        if p >= n:
            break
        c = src[p]
        start = p
        if c == 0x0A:  # newline ending a directive
            toks.append(("pp_end", p, p + 1, b"\n", s))
            p += 1
            s = S_LINE_START
            continue
        kind = None
        if s & S_INCLUDE and c in (0x3C, 0x22):
            m = (_HDR_ANGLE if c == 0x3C else _HDR_QUOTE).match(src, p)
            if m:
                kind, end = "header_name", m.end()
        if kind is None:
            m = _ID.match(src, p)
            if m:
                end = m.end()
                text = src[p:end]
                q = src[end:end + 1]
                if text in _PREFIX and q in (b'"', b"'"):
                    m2 = (_STR if q == b'"' else _CHR).match(src, end)
                    if m2:
                        kind, end = ("string" if q == b'"' else "char"), m2.end()
                if kind is None:
                    kind = "keyword" if text in KEYWORDS else "ident"
            elif c == 0x22 or c == 0x27:
                m = (_STR if c == 0x22 else _CHR).match(src, p)
                if m:
                    kind, end = ("string" if c == 0x22 else "char"), m.end()
                else:
                    kind, end = "unknown", p + 1
            else:
                m = _NUM.match(src, p)
                if m:
                    kind, end = "number", m.end()
                else:
                    m = _PUNCT.match(src, p)
                    if m:
                        end = m.end()
                        kind = src[p:end].decode()
                    else:
                        kind, end = "unknown", p + 1
        text = src[start:end]
        toks.append((kind, start, end, text, s))
        s = sigma_after(s, kind, text)
        p = end
    return toks


if __name__ == "__main__":
    import sys
    data = open(sys.argv[1], "rb").read()
    for t in tokenize(data)[:200]:
        print(t[0], t[1], t[2], t[3][:40], t[4])
