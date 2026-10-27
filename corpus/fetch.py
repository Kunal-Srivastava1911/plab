"""Clone the PLAB corpus (spec section 8.2): shallow, pinned to tags.

Usage: python corpus/fetch.py [--only name,name]
Repos land in corpus/src/<name>. Re-running skips repos that already exist.
"""
import argparse
import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
SRC = ROOT / "src"

# name, url, tag, sparse dirs (None = full checkout), language, split
REPOS = [
    ("git", "https://github.com/git/git", "v2.47.0", None, "c", "train"),
    ("curl", "https://github.com/curl/curl", "curl-8_10_1", None, "c", "train"),
    ("linux", "https://github.com/torvalds/linux", "v6.11", ["kernel", "mm", "fs"], "c", "train"),
    ("sqlite", "https://github.com/sqlite/sqlite", "version-3.46.1", None, "c", "test"),
    ("redis", "https://github.com/redis/redis", "7.4.1", None, "c", "test"),
    ("lua", "https://github.com/lua/lua", "v5.4.7", None, "c", "test"),
    ("nginx", "https://github.com/nginx/nginx", "release-1.27.2", None, "c", "test"),
    ("cpython", "https://github.com/python/cpython", "v3.12.7", ["Lib"], "python", "train"),
    ("django", "https://github.com/django/django", "5.1.2", None, "python", "train"),
    ("requests", "https://github.com/psf/requests", "v2.32.3", None, "python", "test"),
    ("flask", "https://github.com/pallets/flask", "3.0.3", None, "python", "test"),
    ("rich", "https://github.com/Textualize/rich", "v13.9.2", None, "python", "test"),
]


def git(*args, cwd=None):
    print("+ git", " ".join(args), flush=True)
    subprocess.run(["git", "-c", "core.longpaths=true", *args], cwd=cwd, check=True)


def fetch(name, url, tag, sparse):
    dest = SRC / name
    if (dest / ".git").exists():
        print(f"[skip] {name} already present")
        return
    args = ["clone", "--depth", "1", "--branch", tag, "--single-branch"]
    if not sparse:
        git(*args, url, str(dest))
        return
    # linux has paths Windows rejects (drivers/.../aux.c): set the sparse cone before checkout
    git(*args, "--filter=blob:none", "--no-checkout", url, str(dest))
    git("sparse-checkout", "set", "--cone", *sparse, cwd=dest)
    git("-c", "core.protectNTFS=false", "checkout", tag, cwd=dest)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--only", default="")
    args = ap.parse_args()
    only = set(filter(None, args.only.split(",")))
    SRC.mkdir(parents=True, exist_ok=True)
    manifest = []
    failed = []
    for name, url, tag, sparse, lang, split in REPOS:
        try:
            if not only or name in only:
                fetch(name, url, tag, sparse)
            if not (SRC / name / ".git").exists():
                continue
            rev = subprocess.run(["git", "rev-parse", "HEAD"], cwd=SRC / name,
                                 capture_output=True, text=True).stdout.strip()
            manifest.append({"name": name, "url": url, "tag": tag, "rev": rev,
                             "lang": lang, "split": split, "sparse": sparse})
        except subprocess.CalledProcessError as e:
            print(f"[error] {name}: {e}", file=sys.stderr)
            failed.append(name)
    (ROOT / "manifest.json").write_text(json.dumps(manifest, indent=2))
    if failed:
        print("failed:", ", ".join(failed), file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
