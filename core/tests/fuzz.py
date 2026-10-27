"""Mutation fuzzer for PLAB exactness (spec 8.5), the Windows stand-in for libFuzzer.

Mutations concentrate on token boundaries and on bytes from the EXTENDS sets; code is also
duplicated so the copy predictor fires on near-identical phrases. Each batch is checked with
plab_difftest under every configuration; failing inputs are saved to core/tests/regressions/.

Usage: python core/tests/fuzz.py [--iterations 3000] [--batch 100] [--seed 1]
"""
import argparse
import random
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "limitstudy"))
import ctok  # noqa: E402

EXE = ".exe" if sys.platform == "win32" else ""
DIFFTEST = ROOT / "core" / "build" / f"plab_difftest{EXE}"
TABLE, KTABLE = ROOT / "tables" / "c.plabt", ROOT / "tables" / "c_kind.plabt"
REGRESSIONS = ROOT / "core" / "tests" / "regressions"
INTERESTING = sorted(set().union(*ctok.EXTENDS.values()) | set(b"\\\n\r\"'/*#<>%:.eE+-"))


def mutate(src: bytes, rng: random.Random) -> bytes:
    toks = ctok.tokenize(src)
    if not toks:
        return src + bytes([rng.choice(INTERESTING)])
    b = bytearray(src)
    for _ in range(rng.randint(1, 6)):
        t = rng.choice(toks)
        at = min(len(b), rng.choice((t[1], t[2], t[2] + 1)))
        op = rng.random()
        c = rng.choice(INTERESTING)
        if op < 0.35:
            b[at:at] = bytes([c])
        elif op < 0.6 and at < len(b):
            b[at] = c
        elif op < 0.75 and at < len(b):
            del b[at]
        elif op < 0.9:
            # duplicate a nearby chunk with one change so copy drafts almost match
            s = max(0, at - rng.randint(8, 80))
            chunk = bytearray(b[s:at])
            if chunk:
                chunk[rng.randrange(len(chunk))] = c
            b[at:at] = bytes(chunk) * rng.randint(2, 4)
        else:
            b[at:at] = rng.choice((b"\\\n", b"/*", b"*/", b"\n#", b"%:", b"<:", b"...", b"'", b'"', b"u8"))
    return bytes(b)


def check(files):
    cmd = [str(DIFFTEST), "--quiet"]
    if TABLE.exists():
        cmd += ["--table", str(TABLE)]
    if KTABLE.exists():
        cmd += ["--kind-table", str(KTABLE)]
    r = subprocess.run(cmd + [str(f) for f in files], capture_output=True, text=True)
    return r.returncode == 0, r.stderr


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iterations", type=int, default=3000)
    ap.add_argument("--batch", type=int, default=100)
    ap.add_argument("--seed", type=int, default=1)
    args = ap.parse_args()
    rng = random.Random(args.seed)
    seeds = sorted((ROOT / "corpus" / "src" / "lua").glob("*.c")) + \
        sorted((ROOT / "corpus" / "src" / "redis" / "src").glob("*.c"))[:40]
    seeds = [p.read_bytes()[:20000] for p in seeds]
    REGRESSIONS.mkdir(parents=True, exist_ok=True)
    found = 0
    with tempfile.TemporaryDirectory() as tmp:
        done = 0
        while done < args.iterations:
            files = []
            for i in range(min(args.batch, args.iterations - done)):
                data = rng.choice(seeds)
                for _ in range(rng.randint(1, 3)):
                    data = mutate(data, rng)
                f = Path(tmp) / f"case_{i}.c"
                f.write_bytes(data)
                files.append(f)
            done += len(files)
            ok, err = check(files)
            if not ok:
                for f in files:
                    if not check([f])[0]:
                        found += 1
                        dst = REGRESSIONS / f"fuzz_{args.seed}_{done}_{f.stem}.c"
                        dst.write_bytes(f.read_bytes())
                        print(f"FAILURE saved to {dst}")
                print(err[:2000])
            print(f"{done} cases, {found} failures", flush=True)
    sys.exit(1 if found else 0)


if __name__ == "__main__":
    main()
