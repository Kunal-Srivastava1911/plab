"""PLAB pipeline: build, file lists, tables, difftest, bench, traces, limit study, sync.

Usage: python scripts/run_all.py [step ...]
Steps: build lists adversarial tables difftest fuzz bench traces limitstudy sync (default: all)
"""
import datetime
import json
import platform
import random
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
CORE = ROOT / "core"
BUILD = CORE / "build"
CORPUS = ROOT / "corpus"
LISTS = ROOT / "build_lists"
TABLES = ROOT / "tables"
RESULTS = ROOT / "results"
WEB = ROOT / "web"
EXE = ".exe" if sys.platform == "win32" else ""
MAX_FILE = 2 << 20

# files shown in the token inspector: (name, repo-relative path)
TRACE_FILES = [
    ("lua_lvm", "lua/lvm.c"),
    ("lua_lparser", "lua/lparser.c"),
    ("redis_t_list", "redis/src/t_list.c"),
    ("redis_dict", "redis/src/dict.c"),
    ("nginx_http_parse", "nginx/src/http/ngx_http_parse.c"),
    ("sqlite_btree", "sqlite/src/btree.c"),
    ("adv_renamed_lvm", "../adversarial/renamed/lua__lvm.c"),
]


def tool(name):
    return str(BUILD / f"{name}{EXE}")


def run(cmd, **kw):
    print("+", " ".join(str(c) for c in cmd), flush=True)
    return subprocess.run([str(c) for c in cmd], **kw)


def meta(runs):
    def out(cmd):
        try:
            return subprocess.run(cmd, capture_output=True, text=True, timeout=30).stdout.strip()
        except Exception:
            return ""
    cpu = out(["powershell", "-NoProfile", "-Command",
               "(Get-CimInstance Win32_Processor | Select-Object -First 1).Name"]) or platform.processor()
    cc = (out(["gcc", "--version"]).splitlines() or ["unknown"])[0]
    m = {"commit": "no-git", "date": datetime.date.today().isoformat(), "machine": platform.node(),
         "cpu": cpu, "compiler": cc, "flags": "-O2 -march=native", "runs": runs}
    path = LISTS / f"meta_{runs}.json"
    path.write_text(json.dumps(m))
    return path


def repo_files(lang, split):
    manifest = json.loads((CORPUS / "manifest.json").read_text())
    ext = (".c", ".h") if lang == "c" else (".py",)
    out = []
    for repo in manifest:
        if repo["lang"] == lang and repo["split"] == split:
            for p in sorted((CORPUS / "src" / repo["name"]).rglob("*")):
                if p.suffix in ext and p.is_file() and ".git" not in p.parts and 0 < p.stat().st_size <= MAX_FILE:
                    out.append((repo["name"], p))
    return out


def step_build():
    run(["cmake", "-S", CORE, "-B", BUILD, "-G", "Ninja"], check=True)
    run(["cmake", "--build", BUILD], check=True)


def step_lists():
    LISTS.mkdir(exist_ok=True)
    train = repo_files("c", "train")
    test = repo_files("c", "test")
    (LISTS / "train_c.txt").write_text("".join(f"{p}\n" for _, p in train))
    (LISTS / "test_c.txt").write_text("".join(f"{p}\n" for _, p in test))
    lines = [f"test:{r}\t{p}\n" for r, p in test]
    adv = CORPUS / "adversarial"
    if adv.exists():
        for d in sorted(x for x in adv.iterdir() if x.is_dir()):
            lines += [f"adversarial:{d.name}\t{p}\n" for p in sorted(d.glob("*.c"))]
    (LISTS / "bench_c.txt").write_text("".join(lines))
    print(f"lists: {len(train)} train, {len(test)} test C files")


def step_adversarial():
    run([sys.executable, CORPUS / "adversarial.py"], check=True)


def step_tables():
    TABLES.mkdir(exist_ok=True)
    run([tool("plab_build_table"), "--list", LISTS / "train_c.txt", "--out", TABLES / "c.plabt"], check=True)
    run([tool("plab_build_table"), "--list", LISTS / "train_c.txt", "--out", TABLES / "c_kind.plabt",
         "--kind-only"], check=True)


def step_difftest():
    files = (LISTS / "test_c.txt").read_text().splitlines()
    files += [str(p) for p in sorted((CORPUS / "adversarial").rglob("*.c"))]
    train = (LISTS / "train_c.txt").read_text().splitlines()
    files += random.Random(7).sample(train, min(400, len(train)))
    files += [str(p) for p in sorted((CORE / "tests" / "regressions").glob("*.c"))]
    lst = LISTS / "difftest_c.txt"
    lst.write_text("\n".join(files) + "\n")
    RESULTS.mkdir(exist_ok=True)
    r = run([tool("plab_difftest"), "--quiet", "--list", lst, "--table", TABLES / "c.plabt",
             "--kind-table", TABLES / "c_kind.plabt", "--out", RESULTS / "difftest.json",
             "--meta", meta(1)])
    if r.returncode:
        sys.exit("difftest found divergences")


def step_fuzz():
    run([sys.executable, CORE / "tests" / "fuzz.py", "--iterations", "3000"], check=True)


def step_bench():
    run([tool("plab_bench"), "--list", LISTS / "bench_c.txt", "--table", TABLES / "c.plabt",
         "--kind-table", TABLES / "c_kind.plabt", "--runs", "30", "--ablation-runs", "15",
         "--out", RESULTS / "bench.json", "--meta", meta(30)], check=True)


def step_traces():
    out = WEB / "public" / "traces"
    out.mkdir(parents=True, exist_ok=True)
    lines = []
    for name, rel in TRACE_FILES:
        p = (CORPUS / "src" / rel).resolve()
        if p.exists():
            lines.append(f"{name}\t{rel.replace('../', '')}\t{p}\n")
    lst = LISTS / "traces.txt"
    lst.write_text("".join(lines))
    run([tool("plab_trace"), "--table", TABLES / "c.plabt", "--list", lst, "--out-dir", out,
         "--meta", meta(1)], check=True)


def step_limitstudy():
    run([sys.executable, ROOT / "limitstudy" / "run.py"], check=True)


def step_sync():
    dst = WEB / "public" / "results"
    dst.mkdir(parents=True, exist_ok=True)
    for f in ("limit_study.json", "bench.json", "difftest.json"):
        if (RESULTS / f).exists():
            shutil.copy2(RESULTS / f, dst / f)
            print(f"synced {f}")


STEPS = {"build": step_build, "lists": step_lists, "adversarial": step_adversarial, "tables": step_tables,
         "difftest": step_difftest, "fuzz": step_fuzz, "bench": step_bench, "traces": step_traces,
         "limitstudy": step_limitstudy, "sync": step_sync}

if __name__ == "__main__":
    LISTS.mkdir(exist_ok=True)
    for s in sys.argv[1:] or list(STEPS):
        STEPS[s]()
