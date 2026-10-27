"""Phase 0 limit study: predictor simulator and static-table miner (spec 8.1).

Mirrors the predictor logic of spec 5.2 and the acceptance rule of section 3:
copy predictor (4096 entries, 16-bit tags, 2-bit confidence, 64-entry training ring),
static primary-order and order-1 tables (direct mapped, 16-bit tags), selection order
copy -> static primary -> static order-1, at most 8 tokens and W bytes per phrase.
C uses the guard rule (EXTENDS sets); Python uses an oracle (recorded tokens must
equal the actual tokens), recorded as "acceptance" in each run.
"""
import zlib
from collections import defaultdict

import ctok

M64 = (1 << 64) - 1
P1, P2, P3 = 0x9E3779B97F4A7C15, 0xC2B2AE3D27D4EB4F, 0x165667B19E3779F9
SALT1 = 0x5BD1E9955BD1E995
MAXTOK = 8


def mix64(z):
    z &= M64
    z = ((z ^ (z >> 30)) * 0xBF58476D1CE4E5B9) & M64
    z = ((z ^ (z >> 27)) * 0x94D049BB133111EB) & M64
    return z ^ (z >> 31)


class FileData:
    __slots__ = ("name", "src", "n", "kind", "start", "end", "cid", "kcid", "sig", "stop",
                 "last", "sig0", "ext")

    def __init__(self, name, src, toks, lang, kind_ids):
        self.name = name
        self.src = src
        self.n = len(toks)
        self.kind = [kind_ids.setdefault(t[0], len(kind_ids) + 1) for t in toks]
        self.start = [t[1] for t in toks]
        self.end = [t[2] for t in toks]
        ident = ("ident", "keyword") if lang == "c" else ("NAME",)
        self.cid = [(zlib.crc32(t[3]) | 0x80000000) if t[0] in ident else k
                    for t, k in zip(toks, self.kind)]
        self.kcid = self.kind
        if lang == "c":
            self.sig = [ctok.sigma_after(t[4], t[0], t[3]) for t in toks]
            self.sig0 = ctok.S_LINE_START
            prev = [0] + self.end[:-1]
            self.stop = [t[0] in ctok.NEVER_RECORD or b"\\\n" in src[p:t[2]] or b"\\\r\n" in src[p:t[2]]
                         for t, p in zip(toks, prev)]
            self.last = [t[0] == "pp_end" for t in toks]
        else:
            self.sig = [toks[i + 1][4] if i + 1 < len(toks) else 0 for i in range(len(toks))]
            self.sig0 = 0
            self.stop = [t[0] == "ERRORTOKEN" for t in toks]
            self.last = [False] * len(toks)

    def base(self, i):
        return self.end[i] if i >= 0 else 0

    def sigma(self, i):
        return self.sig[i] if i >= 0 else self.sig0

    def phrase_len(self, i, W, limit=None):
        """Number of tokens (<= 8) in the phrase recorded after token i."""
        base = self.base(i)
        hi = min(self.n - 1, i + MAXTOK)
        if limit is not None:
            hi = min(hi, limit)
        m = 0
        for j in range(i + 1, hi + 1):
            if self.stop[j] or self.end[j] - base > W:
                break
            m += 1
            if self.last[j]:
                break
        return m

    def ctx(self, i, order, kind_only):
        c = self.kcid if kind_only else self.cid
        s = self.sigma(i)
        c1 = c[i] if i >= 0 else 0
        if order == 1:
            return mix64(c1 * P2 ^ s ^ SALT1)
        c2 = c[i - 1] if i >= 1 else 0
        if order == 2:
            return mix64(c2 * P1 ^ c1 * P2 ^ s)
        c3 = c[i - 2] if i >= 2 else 0
        return mix64(c3 * P3 ^ c2 * P1 ^ c1 * P2 ^ s)


class Rec:
    __slots__ = ("tag", "sigma_in", "bytes", "toks", "source")

    def __init__(self, fd, i, m, source, tag=0):
        base = fd.base(i)
        self.tag = tag
        self.sigma_in = fd.sigma(i)
        self.bytes = fd.src[base:fd.end[i + m]]
        self.toks = [(fd.start[k] - base, fd.end[k] - base, fd.kind[k]) for k in range(i + 1, i + m + 1)]
        self.source = source


# ---------------------------------------------------------------- mining

def mine(train, order, kind_only, top_ctx=40000):
    """Count phrase prefixes per context. Returns {ctx: [(count, ntok, nbytes, fd, i), ...]}."""
    ctx_count = defaultdict(int)
    for fd in train:
        for i in range(-1, fd.n - 1):
            ctx_count[fd.ctx(i, order, kind_only)] += 1
    keep = sorted((c for c in ctx_count.items() if c[1] >= 2), key=lambda c: -c[1])[:top_ctx]
    keep = {h for h, _ in keep}
    del ctx_count
    cnt = {}
    for fd in train:
        src, end = fd.src, fd.end
        for i in range(-1, fd.n - 1):
            h = fd.ctx(i, order, kind_only)
            if h not in keep:
                continue
            m = fd.phrase_len(i, 64)
            base = fd.base(i)
            for j in range(1, m + 1):
                key = (h, src[base:end[i + j]])
                e = cnt.get(key)
                if e is None:
                    cnt[key] = [1, j, fd, i]
                else:
                    e[0] += 1
    by_ctx = defaultdict(list)
    for (h, b), (c, j, fd, i) in cnt.items():
        if c >= 2:
            by_ctx[h].append((c, j, len(b), fd, i))
    return by_ctx


def build_table(by_ctx, nslots, W, source):
    """Direct-mapped table of nslots records: best phrase per context by count * tokens."""
    if nslots <= 0:
        return None
    scored = []
    for h, cands in by_ctx.items():
        best = None
        for c, j, nb, fd, i in cands:
            if nb <= W and (best is None or (c * j, j) > (best[0] * best[1], best[1])):
                best = (c, j, fd, i)
        if best:
            scored.append((best[0] * best[1], h, best))
    scored.sort(key=lambda x: -x[0])
    table = [None] * nslots
    mask = nslots - 1
    for _, h, (c, j, fd, i) in scored:
        slot = h & mask
        if table[slot] is None:
            table[slot] = Rec(fd, i, j, source, tag=h >> 48)
    return table


# ---------------------------------------------------------------- simulation

class Stats:
    def __init__(self):
        self.tokens = self.bytes = self.files = 0
        self.committed = self.committed_bytes = 0
        self.phrases = self.partial = self.probes = self.failed = self.fallback = 0
        self.by_source = defaultdict(int)
        self.hist = [0] * MAXTOK
        self.violations = 0
        self.lookups = self.trains = 0


def simulate(test, cfg, tables, stats):
    """cfg: dict(order, kind_only, W, copy, static, acceptance) plus predictor variants:
    copy_orders (list, longest first), copy_sizes, conf_min, train_committed, max_probes."""
    order, kind_only, W = cfg["order"], cfg["kind_only"], cfg["W"]
    use_copy, use_static, guard = cfg["copy"], cfg["static"], cfg["acceptance"] == "guard"
    corders = cfg.get("copy_orders") or [order]
    csizes = cfg.get("copy_sizes") or [4096 // len(corders)] * len(corders)
    conf_min = cfg.get("conf_min", 2)
    train_committed = cfg.get("train_committed", False)
    max_probes = cfg.get("max_probes", 1)
    # anchors: predict and train only right after tokens of these kinds; train_every: sample training
    anchors = cfg.get("anchors")
    if anchors is not None:
        anchors = {cfg["kind_ids"][k] for k in anchors if k in cfg["kind_ids"]}
    train_every = cfg.get("train_every", 1)
    prim, o1, prim_name = tables
    pmask = len(prim) - 1 if prim else 0
    omask = len(o1) - 1 if o1 else 0
    EXT = ctok.EXTENDS
    kname = {v: k for k, v in cfg["kind_ids"].items()}
    for fd in test:
        stats.files += 1
        stats.tokens += fd.n
        stats.bytes += len(fd.src)
        src, n, kind, start, end = fd.src, fd.n, fd.kind, fd.start, fd.end
        copies = [[None] * sz for sz in csizes]
        sconf = {}
        ring = []

        tcount = [0]

        def enqueue(i):
            if anchors is not None and i >= 0 and kind[i] not in anchors:
                return
            tcount[0] += 1
            if tcount[0] % train_every:
                return
            stats.trains += 1
            for c, (o, sz) in enumerate(zip(corders, csizes)):
                ring.append((c, fd.ctx(i, o, kind_only), i))
            if len(ring) >= 64 * len(corders):
                for c, hh, ti in ring:
                    tab = copies[c]
                    idx, tag = hh % len(tab), hh >> 48
                    e = tab[idx]
                    if e is not None and e[0] == tag:
                        o_ = e[2]
                        if o_ + 1 < n and ti + 1 < n and kind[o_ + 1] == kind[ti + 1] and                                 src[start[o_ + 1]:end[o_ + 1]] == src[start[ti + 1]:end[ti + 1]]:
                            e[1] = min(3, e[1] + 1)
                        else:
                            e[1] = max(0, e[1] - 1)
                        e[2] = ti
                    elif e is not None and e[1] > 0:
                        e[1] -= 1
                    else:
                        tab[idx] = [tag, 1, ti]
                ring.clear()

        i = -1
        while i < n - 1:
            if anchors is not None and i >= 0 and kind[i] not in anchors:
                stats.fallback += 1
                i += 1
                continue
            stats.lookups += 1
            s = fd.sigma(i)
            cands = []  # (rec, conf entry or None, static key or None)
            if use_copy:
                for c, o in enumerate(corders):
                    tab = copies[c]
                    hh = fd.ctx(i, o, kind_only)
                    e = tab[hh % len(tab)]
                    if e is not None and e[0] == hh >> 48 and e[1] >= conf_min:
                        ti = e[2]
                        if fd.sigma(ti) == s:
                            m = fd.phrase_len(ti, W, limit=i)
                            if m:
                                cands.append((Rec(fd, ti, m, "copy"), e, None))
                                break
            if use_static and len(cands) < max_probes:
                for tab, mask, name, hh in ((prim, pmask, prim_name, None), (o1, omask, "static_o1", None)):
                    if tab is None:
                        continue
                    hh = fd.ctx(i, 1 if name == "static_o1" else order, kind_only)
                    slot = hh & mask
                    r = tab[slot]
                    if r is not None and r.tag == hh >> 48 and r.sigma_in == s                             and sconf.get((name, slot), 3) >= 2:
                        cands.append((r, None, (name, slot)))
                        break
            j = 0
            rec = None
            for rec, centry, skey in cands[:max_probes]:
                stats.probes += 1
                base = fd.base(i)
                rb = rec.bytes
                L = len(rb)
                actual = src[base:base + L]
                if actual == rb:
                    a = L
                else:
                    a = 0
                    while a < len(actual) and actual[a] == rb[a]:
                        a += 1
                j = 0
                if guard:
                    for k in range(len(rec.toks) - 1, -1, -1):
                        e_ = rec.toks[k][1]
                        if e_ <= a:
                            nb = src[base + e_] if base + e_ < len(src) else 0
                            if nb not in EXT[kname[rec.toks[k][2]]]:
                                j = k + 1
                                break
                else:
                    for k, (rs, re_, kd) in enumerate(rec.toks):
                        t = i + 1 + k
                        if re_ > a or t >= n or start[t] != base + rs or end[t] != base + re_ or kind[t] != kd:
                            break
                        j = k + 1
                if cfg.get("no_partial") and j < len(rec.toks):
                    j = 0
                if centry is not None:
                    centry[1] = min(3, centry[1] + 1) if j else max(0, centry[1] - 1)
                elif skey is not None:
                    sconf[skey] = min(3, sconf.get(skey, 3) + 1) if j else max(0, sconf.get(skey, 3) - 1)
                if j:
                    break
                stats.failed += 1
            if j:
                base = fd.base(i)
                if guard:
                    for k in range(j):
                        t = i + 1 + k
                        rs, re_, kd = rec.toks[k]
                        if t >= n or start[t] != base + rs or end[t] != base + re_ or kind[t] != kd:
                            stats.violations += 1
                            break
                stats.committed += j
                stats.committed_bytes += end[i + j] - base
                stats.phrases += 1
                stats.partial += j < len(rec.toks)
                stats.by_source[rec.source] += j
                stats.hist[j - 1] += 1
                if use_copy and train_committed:
                    for t in range(max(0, i), i + j):
                        enqueue(t)
                i += j
                continue
            # fallback: baseline lexes one token; train the copy predictor via the ring
            stats.fallback += 1
            if use_copy and i >= 0:
                enqueue(i)
            i += 1
    return stats


def summarize(st):
    tot = max(1, st.committed)
    return {
        "files": st.files, "tokens": st.tokens, "bytes": st.bytes,
        "coverage_tokens": st.committed / max(1, st.tokens),
        "coverage_bytes": st.committed_bytes / max(1, st.bytes),
        "mean_tokens_per_phrase": st.committed / max(1, st.phrases),
        "failed_probe_rate": st.failed / max(1, st.fallback),
        "partial_accept_rate": st.partial / max(1, st.phrases),
        "by_source": {k: v / tot for k, v in sorted(st.by_source.items())},
        "phrase_len_hist": st.hist,
        "probes": st.probes, "failed_probes": st.failed,
        "exactness_violations": st.violations,
    }
