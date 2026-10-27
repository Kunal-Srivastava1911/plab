"""Generate the adversarial C set (spec 8.2) into corpus/adversarial/<kind>/.

renamed      identifiers (not keywords) renamed to random strings, one mapping per file
shuffled     lines shuffled within each function body
minified     comments removed, whitespace minimized to what keeps the token stream
thrash       synthetic code alternating two continuations per context
tiny         real files cut into pieces under 1 KB at line boundaries
"""
import random
import string
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT.parent / "limitstudy"))
import ctok  # noqa: E402

OUT = ROOT / "adversarial"
SOURCES = ["lua", "redis", "nginx", "sqlite"]
FILES_PER_REPO = 12


def pick_sources(rng):
    out = []
    for repo in SOURCES:
        files = sorted(p for p in (ROOT / "src" / repo).rglob("*.c")
                       if ".git" not in p.parts and 4096 < p.stat().st_size < 200_000)
        rng.shuffle(files)
        out += [(repo, f) for f in files[:FILES_PER_REPO]]
    return out


def renamed(src, rng):
    mapping = {}
    out, prev = [], 0
    for kind, s, e, text, sig in ctok.tokenize(src):
        out.append(src[prev:s])
        if kind == "ident" and not (sig & ctok.S_DNAME):
            if text not in mapping:
                n = rng.randint(3, 12)
                mapping[text] = (rng.choice(string.ascii_letters) +
                                 "".join(rng.choice(string.ascii_letters + string.digits + "_") for _ in range(n))).encode()
            out.append(mapping[text])
        else:
            out.append(text)
        prev = e
    out.append(src[prev:])
    return b"".join(out)


def shuffled(src, rng):
    lines = src.split(b"\n")
    out, body = [], None
    for ln in lines:
        if body is None:
            out.append(ln)
            if ln.startswith(b"{"):
                body = []
        elif ln.startswith(b"}"):
            rng.shuffle(body)
            out += body + [ln]
            body = None
        else:
            body.append(ln)
    if body:
        out += body
    return b"\n".join(out)


def minified(src, rng):
    out = []
    prev_kind = None
    for kind, s, e, text, sig in ctok.tokenize(src):
        if kind == "pp_end":
            out.append(b"\n")
            prev_kind = None
            continue
        if (sig & ctok.S_LINE_START) and out and out[-1] != b"\n" and kind in ("#", "%:"):
            out.append(b"\n")
        elif prev_kind is not None and text[0] in ctok.EXTENDS[prev_kind]:
            out.append(b" ")
        elif prev_kind in ("ident", "keyword", "number") and kind in ("string", "char"):
            out.append(b" ")
        out.append(text)
        prev_kind = kind
    return b"".join(out) + b"\n"


def thrash(rng, size=600_000):
    """Every context is followed by two continuations in alternation: confidence never settles."""
    names = ["a", "b", "c", "d", "e", "f", "g", "h"]
    ops = [("+", "-"), ("*", "/"), ("<<", ">>"), ("&", "|"), ("==", "!="), ("<", ">")]
    parts = ["int " + ", ".join(names) + ";\nvoid f(void) {\n"]
    total, k = 0, 0
    while total < size:
        x, y, z = rng.sample(names, 3)
        o = ops[k % len(ops)][k & 1]
        line = f"    {x} = {y} {o} {z};\n" if k % 3 else f"    if ({x} {o} {y}) {z}++; else {z}--;\n"
        parts.append(line)
        total += len(line)
        k += 1
    parts.append("}\n")
    return "".join(parts).encode()


def tiny(src):
    pieces, cur = [], []
    size = 0
    for ln in src.split(b"\n"):
        if size + len(ln) + 1 > 1000 and cur:
            pieces.append(b"\n".join(cur) + b"\n")
            cur, size = [], 0
        if len(ln) < 1000:
            cur.append(ln)
            size += len(ln) + 1
    if cur:
        pieces.append(b"\n".join(cur) + b"\n")
    return pieces


def main():
    rng = random.Random(2026)
    for d in ("renamed", "shuffled", "minified", "thrash", "tiny"):
        (OUT / d).mkdir(parents=True, exist_ok=True)
        for f in (OUT / d).glob("*.c"):
            f.unlink()
    srcs = pick_sources(rng)
    for repo, f in srcs:
        data = f.read_bytes()
        name = f"{repo}__{f.stem}.c"
        (OUT / "renamed" / name).write_bytes(renamed(data, rng))
        (OUT / "shuffled" / name).write_bytes(shuffled(data, rng))
        (OUT / "minified" / name).write_bytes(minified(data, rng))
    for i in range(4):
        (OUT / "thrash" / f"thrash_{i}.c").write_bytes(thrash(random.Random(i)))
    n = 0
    for repo, f in srcs[::4]:
        for piece in tiny(f.read_bytes())[:40]:
            (OUT / "tiny" / f"{repo}__{f.stem}_{n:04d}.c").write_bytes(piece)
            n += 1
    # the inspector shows a renamed lua/lvm.c next to the original
    lvm = ROOT / "src" / "lua" / "lvm.c"
    if lvm.exists():
        (OUT / "renamed" / "lua__lvm.c").write_bytes(renamed(lvm.read_bytes(), rng))
    for d in sorted(OUT.iterdir()):
        files = list(d.glob("*.c"))
        print(f"{d.name:10s} {len(files):5d} files {sum(p.stat().st_size for p in files) / 1e6:6.2f} MB")


if __name__ == "__main__":
    main()
