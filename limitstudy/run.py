"""Run the Phase 0 limit study sweeps and write results/limit_study.json (schema 9.1).

Usage: python limitstudy/run.py [--lang c,python] [--train-mb 8] [--test-mb 10]
"""
import argparse
import datetime
import json
import platform
import random
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ctok  # noqa: E402
import pytok  # noqa: E402
import sim  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
CORPUS = ROOT / "corpus"
COST = {"C_hit": 10, "n": 4, "C_ctx": 1, "C_p": 6, "P_br": 17}
BASELINES = {"simd": 8, "re2c": 15, "flex": 30}
EXT = {"c": (".c", ".h"), "python": (".py",)}
MAX_FILE = 2 << 20


def cpu_name():
    try:
        import subprocess
        out = subprocess.run(["powershell", "-NoProfile", "-Command",
                              "(Get-CimInstance Win32_Processor | Select-Object -First 1).Name"],
                             capture_output=True, text=True, timeout=20).stdout.strip()
        return out or platform.processor()
    except Exception:
        return platform.processor()


def meta(runs=1):
    return {"commit": "no-git", "date": datetime.date.today().isoformat(),
            "machine": platform.node(), "cpu": cpu_name(),
            "compiler": f"CPython {platform.python_version()}", "flags": "", "runs": runs}


def corpus_files(lang, split):
    manifest = json.loads((CORPUS / "manifest.json").read_text())
    files = []
    for repo in manifest:
        if repo["lang"] != lang or repo["split"] != split:
            continue
        for p in sorted((CORPUS / "src" / repo["name"]).rglob("*")):
            if p.suffix in EXT[lang] and p.is_file() and ".git" not in p.parts \
                    and 0 < p.stat().st_size <= MAX_FILE:
                files.append(p)
    return files


def sample(files, cap_bytes, seed):
    files = list(files)
    random.Random(seed).shuffle(files)
    out, total = [], 0
    for f in files:
        if total >= cap_bytes:
            break
        out.append(f)
        total += f.stat().st_size
    return sorted(out)


def load(files, lang, kind_ids):
    out = []
    for f in files:
        src = f.read_bytes()
        try:
            toks = ctok.tokenize(src) if lang == "c" else pytok.tokenize_bytes(src)
        except Exception:
            continue
        out.append(sim.FileData(str(f.relative_to(CORPUS / "src")), src, toks, lang, kind_ids))
    return out


def break_even(c_ref, g):
    F = COST["C_ctx"] + g * (COST["C_p"] + COST["P_br"])
    return F / (c_ref + F - COST["C_hit"] / COST["n"])


def study(lang, train_mb, test_mb, log):
    kind_ids = {}
    t0 = time.time()
    train = load(sample(corpus_files(lang, "train"), train_mb << 20, 1), lang, kind_ids)
    test = load(sample(corpus_files(lang, "test"), test_mb << 20, 2), lang, kind_ids)
    log(f"[{lang}] train {len(train)} files {sum(f.n for f in train)} tok, "
        f"test {len(test)} files {sum(f.n for f in test)} tok ({time.time() - t0:.0f}s)")
    acceptance = "guard" if lang == "c" else "oracle"

    mined = {}

    def get_mined(order, kind_only):
        key = (order, kind_only)
        if key not in mined:
            t = time.time()
            mined[key] = sim.mine(train, order, kind_only)
            log(f"[{lang}] mined order={order} kind_only={kind_only}: {len(mined[key])} contexts "
                f"({time.time() - t:.0f}s)")
        return mined[key]

    def run(predictor, budget_kb, order, W, kind_only=False):
        nrec = budget_kb * 1024 // 128
        use_static = predictor in ("both", "static", "markov_kind", "cascade")
        use_copy = predictor in ("both", "copy", "markov_kind", "cascade")
        prim = o1 = None
        prim_name = f"static_o{order}"
        if use_static:
            if order == 1:
                prim, prim_name = sim.build_table(get_mined(1, kind_only), nrec, W, "static_o1"), "static_o1"
            else:
                prim = sim.build_table(get_mined(order, kind_only), nrec // 2, W, prim_name)
                o1 = sim.build_table(get_mined(1, kind_only), nrec // 2, W, "static_o1")
        cfg = {"order": order, "kind_only": kind_only, "W": W, "copy": use_copy,
               "static": use_static, "acceptance": acceptance, "kind_ids": kind_ids}
        if predictor == "cascade":
            # the improved copy predictor (core default): orders 3 > 2 > 1 in the same 4096 entries,
            # confidence >= 1, also trained inside committed phrases
            cfg.update(copy_orders=[3, 2, 1], copy_sizes=[2048, 1024, 1024], conf_min=1, train_committed=True)
        t = time.time()
        st = sim.simulate(test, cfg, (prim, o1, prim_name), sim.Stats())
        row = {"lang": lang, "predictor": predictor, "budget_kb": budget_kb, "order": order, "W": W,
               "acceptance": acceptance}
        row.update(sim.summarize(st))
        bs = {"copy": 0.0, prim_name: 0.0, "static_o1": 0.0}
        bs.update(row["by_source"])
        row["by_source"] = bs
        log(f"[{lang}] {predictor:12s} {budget_kb:5d}KB o{order} W{W}: cov {row['coverage_tokens']:.3f} "
            f"tpp {row['mean_tokens_per_phrase']:.2f} g {row['failed_probe_rate']:.3f} "
            f"viol {row['exactness_violations']} ({time.time() - t:.0f}s)")
        return row

    rows = []
    copy_row = run("copy", 512, 2, 32)
    for b in (32, 128, 512, 2048):
        rows.append(run("cascade", b, 2, 32))
        rows.append(run("both", b, 2, 32))
        rows.append(run("static", b, 2, 32))
        r = dict(copy_row, budget_kb=b)
        rows.append(r)
    for order in (1, 3):
        rows.append(run("both", 512, order, 32))
    for W in (16, 64):
        rows.append(run("both", 512, 2, W))
    rows.append(run("markov_kind", 512, 2, 32, kind_only=True))
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--lang", default="c,python")
    ap.add_argument("--train-mb", type=int, default=8)
    ap.add_argument("--test-mb", type=int, default=10)
    ap.add_argument("--out", default=str(ROOT / "results" / "limit_study.json"))
    args = ap.parse_args()

    def log(msg):
        print(msg, flush=True)

    rows = []
    for lang in args.lang.split(","):
        rows += study(lang, args.train_mb, args.test_mb, log)

    # gate (spec 8.1): coverage and g next to the break-even table
    gate = []
    for r in rows:
        if r["predictor"] == "both" and r["budget_kb"] == 512 and r["order"] == 2 and r["W"] == 32:
            for name, c_ref in BASELINES.items():
                be = break_even(c_ref, r["failed_probe_rate"])
                gate.append({"lang": r["lang"], "baseline": name, "C_ref": c_ref,
                             "g": r["failed_probe_rate"], "break_even": be,
                             "coverage": r["coverage_tokens"], "passes": r["coverage_tokens"] > be})
                log(f"gate {r['lang']:6s} {name:5s} a*={be:.3f} coverage={r['coverage_tokens']:.3f}")
    out = {"meta": meta(), "cost_model_assumptions": COST,
           "sampling": {"train_mb": args.train_mb, "test_mb": args.test_mb},
           "runs": rows, "gate": gate}
    Path(args.out).parent.mkdir(parents=True, exist_ok=True)
    Path(args.out).write_text(json.dumps(out, indent=1))
    log(f"wrote {args.out}")


if __name__ == "__main__":
    main()
