"""Python tokenizer for the limit study: stdlib `tokenize`, byte offsets.

Emits (kind, start, end, text, sigma) like ctok. COMMENT and NL are trivia.
sigma bit 0 = inside brackets (where newlines are not NEWLINE tokens).
"""
import io
import tokenize

TRIVIA = {tokenize.COMMENT, tokenize.NL, tokenize.ENCODING, tokenize.ENDMARKER}
OPEN, CLOSE = set("([{"), set(")]}")


def tokenize_bytes(src: bytes):
    lines = src.split(b"\n")
    starts, off = [], 0
    for ln in lines:
        starts.append(off)
        off += len(ln) + 1
    texts = {}

    def boff(row, col):
        i = row - 1
        if i >= len(lines):
            return len(src)
        if i not in texts:
            texts[i] = lines[i].decode("utf-8", "replace")
        t = texts[i]
        return starts[i] + (col if t.isascii() else len(t[:col].encode("utf-8")))

    toks = []
    depth = 0
    for tok in tokenize.tokenize(io.BytesIO(src).readline):
        if tok.type in TRIVIA:
            continue
        s, e = boff(*tok.start), boff(*tok.end)
        kind = tokenize.tok_name[tok.exact_type]
        sig = 1 if depth else 0
        toks.append((kind, s, e, src[s:e], sig))
        if tok.type == tokenize.OP:
            if tok.string in OPEN:
                depth += 1
            elif tok.string in CLOSE and depth:
                depth -= 1
    return toks
