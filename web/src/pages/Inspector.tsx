import { useEffect, useMemo, useRef, useState, type CSSProperties, type ReactNode } from "react";
import {
  COLORS,
  Empty,
  ErrorBox,
  Loading,
  OutcomeLegend,
  PageHeader,
  SOURCE_COLORS,
  SOURCE_LABELS,
  Toggle,
} from "../components";
import { fetchJson, pct } from "../data";
import type { Outcome, Trace, TraceIndexEntry, TraceToken } from "../types";

const LINE_H = 20;
const BUFFER = 30;
const OUTCOME_BG: Record<Outcome, string> = {
  commit: "var(--c-commit-bg)",
  partial: "var(--c-partial-bg)",
  miss: "var(--c-miss-bg)",
  fallback: "var(--c-fallback-bg)",
};
const OUTCOME_LABEL: Record<Outcome, string> = {
  commit: "Committed (full phrase)",
  partial: "Committed (partial phrase)",
  miss: "Failed probe, then fallback",
  fallback: "Fallback (no confident prediction)",
};

export default function Inspector() {
  const [index, setIndex] = useState<TraceIndexEntry[] | null>(null);
  const [err, setErr] = useState<string | null>(null);
  const [name, setName] = useState<string | null>(null);
  const [trace, setTrace] = useState<Trace | null>(null);
  const [loading, setLoading] = useState(false);

  useEffect(() => {
    fetchJson<{ files: TraceIndexEntry[] }>("traces/index.json")
      .then((d) => {
        setIndex(d.files);
        if (d.files.length) setName(d.files[0].name);
      })
      .catch(() => setErr("traces/index.json is missing. Run python scripts/run_all.py traces."));
  }, []);

  useEffect(() => {
    if (!name) return;
    let live = true;
    setLoading(true);
    fetchJson<Trace>(`traces/${name}.json`)
      .then((t) => live && setTrace(t))
      .catch(() => live && setErr(`traces/${name}.json is missing.`))
      .finally(() => live && setLoading(false));
    return () => {
      live = false;
    };
  }, [name]);

  return (
    <div>
      <PageHeader
        title="Token Inspector"
        sub="Every token of a real file, tinted by how PLAB produced it. Underline bands mark accepted phrases, colored by the predictor that proposed them."
      />
      {err && <ErrorBox message={err} />}
      {!err && !index && <Loading what="trace index" />}
      {index && !index.length && <Empty message="No traces were generated." />}
      {index && index.length > 0 && (
        <>
          <div className="mb-3 flex flex-wrap items-center gap-2">
            {index.map((f) => (
              <button
                key={f.name}
                onClick={() => setName(f.name)}
                className="rounded-md border px-2.5 py-1 text-xs"
                style={{
                  borderColor: f.name === name ? "var(--c-accent)" : "var(--border)",
                  background: f.name === name ? "var(--panel)" : "transparent",
                }}
                title={f.path}
              >
                <span className="font-mono">{f.path}</span>
                <span className="ml-2 font-semibold" style={{ color: COLORS.commit }}>{pct(f.coverage)}</span>
              </button>
            ))}
          </div>
          {loading && <Loading what={name ?? "trace"} />}
          {!loading && trace && trace.name === name && <Viewer key={trace.name} trace={trace} />}
        </>
      )}
    </div>
  );
}

interface Prepared {
  bytes: Uint8Array;
  lineStarts: number[];
  lineTokens: number[][];
  topPhrases: { text: string; count: number; ids: number[]; ntok: number; src: string }[];
  counts: Record<Outcome, number>;
  phrasesAccepted: number;
  committed: number;
}

const decoder = new TextDecoder();

function prepare(t: Trace): Prepared {
  const bytes = new TextEncoder().encode(t.source);
  const lineStarts = [0];
  for (let i = 0; i < bytes.length; i++) if (bytes[i] === 10) lineStarts.push(i + 1);
  const lineOf = (off: number) => {
    let lo = 0, hi = lineStarts.length - 1;
    while (lo < hi) {
      const mid = (lo + hi + 1) >> 1;
      if (lineStarts[mid] <= off) lo = mid;
      else hi = mid - 1;
    }
    return lo;
  };
  const lineTokens: number[][] = lineStarts.map(() => []);
  const counts: Record<Outcome, number> = { commit: 0, partial: 0, miss: 0, fallback: 0 };
  t.tokens.forEach((tok, i) => {
    counts[tok.o]++;
    const a = lineOf(tok.s), b = lineOf(Math.max(tok.s, tok.e - 1));
    for (let l = a; l <= b; l++) lineTokens[l].push(i);
  });
  // group committed tokens by phrase to find the most frequent accepted phrases
  const span = new Map<number, [number, number, number]>();
  for (const tok of t.tokens) {
    if (tok.ph === null || (tok.o !== "commit" && tok.o !== "partial")) continue;
    const s = span.get(tok.ph);
    span.set(tok.ph, s ? [s[0], tok.e, s[2] + 1] : [tok.s, tok.e, 1]);
  }
  const freq = new Map<string, { text: string; count: number; ids: number[]; ntok: number; src: string }>();
  for (const [id, [s, e, n]] of span) {
    const text = decoder.decode(bytes.subarray(s, e)).replace(/\s+/g, " ").trim() || "↵ (directive end)";
    const f = freq.get(text);
    if (f) {
      f.count++;
      f.ids.push(id);
    } else freq.set(text, { text, count: 1, ids: [id], ntok: n, src: t.phrases[id]?.src ?? "" });
  }
  const topPhrases = [...freq.values()].sort((a, b) => b.count * b.ntok - a.count * a.ntok).slice(0, 20);
  return {
    bytes,
    lineStarts,
    lineTokens,
    topPhrases,
    counts,
    phrasesAccepted: span.size,
    committed: counts.commit + counts.partial,
  };
}

function byteChar(b: number | null): string {
  if (b === null) return "–";
  if (b === 10) return "\\n";
  if (b === 9) return "\\t";
  if (b === 32) return "␠";
  if (b === 0) return "EOF";
  return b < 32 || b > 126 ? `0x${b.toString(16)}` : `'${String.fromCharCode(b)}'`;
}

function Viewer({ trace }: { trace: Trace }) {
  const prep = useMemo(() => prepare(trace), [trace]);
  const [showPhrases, setShowPhrases] = useState(true);
  const [onlyMisses, setOnlyMisses] = useState(false);
  const [dimFallback, setDimFallback] = useState(false);
  const [highlight, setHighlight] = useState<Set<number> | null>(null);
  const [hover, setHover] = useState<{ i: number; x: number; y: number } | null>(null);
  const [scrollTop, setScrollTop] = useState(0);
  const [height, setHeight] = useState(600);
  const scroller = useRef<HTMLDivElement>(null);

  useEffect(() => {
    const el = scroller.current;
    if (!el) return;
    const ro = new ResizeObserver(() => setHeight(el.clientHeight));
    ro.observe(el);
    return () => ro.disconnect();
  }, []);

  const nLines = prep.lineStarts.length;
  const first = Math.max(0, Math.floor(scrollTop / LINE_H) - BUFFER);
  const last = Math.min(nLines, Math.ceil((scrollTop + height) / LINE_H) + BUFFER);
  const gutter = String(nLines).length;
  const { tokens, phrases } = trace;
  const tpp = prep.phrasesAccepted ? prep.committed / prep.phrasesAccepted : 0;
  const misses = phrases.filter((p) => p.accepted === 0).length;

  const tokenStyle = (tok: TraceToken): CSSProperties => {
    const st: CSSProperties = { background: OUTCOME_BG[tok.o], borderRadius: 2 };
    if (onlyMisses && tok.o !== "miss") st.opacity = 0.25;
    else if (dimFallback && tok.o === "fallback") st.opacity = 0.35;
    if (highlight && tok.ph !== null && highlight.has(tok.ph)) st.outline = "1.5px solid var(--c-accent)";
    return st;
  };
  const band = (tok: TraceToken): CSSProperties =>
    showPhrases && tok.ph !== null && (tok.o === "commit" || tok.o === "partial")
      ? { boxShadow: `inset 0 -2.5px 0 ${SOURCE_COLORS[tok.src ?? ""] ?? COLORS.accent}` }
      : {};

  const renderLine = (l: number) => {
    const ls = prep.lineStarts[l];
    const le = l + 1 < nLines ? prep.lineStarts[l + 1] - 1 : prep.bytes.length;
    const out: ReactNode[] = [];
    let pos = ls;
    let prev: TraceToken | null = null;
    for (const i of prep.lineTokens[l]) {
      const tok = tokens[i];
      const s = Math.max(tok.s, ls), e = Math.min(tok.e, le);
      if (s > pos) {
        const gap = decoder.decode(prep.bytes.subarray(pos, s));
        const sameBand = prev && prev.ph !== null && prev.ph === tok.ph && (tok.o === "commit" || tok.o === "partial");
        out.push(<span key={`g${i}`} style={sameBand ? band(tok) : undefined}>{gap}</span>);
      }
      if (e > s)
        out.push(
          <span
            key={i}
            style={{ ...tokenStyle(tok), ...band(tok) }}
            onMouseEnter={(ev) => setHover({ i, x: ev.clientX, y: ev.clientY })}
            onMouseLeave={() => setHover(null)}
          >
            {decoder.decode(prep.bytes.subarray(s, e))}
          </span>,
        );
      else if (tok.k === "pp_end" && tok.o !== "fallback") {
        out.push(<span key={i} style={{ ...tokenStyle(tok), ...band(tok) }}>{"↵"}</span>);
      }
      pos = Math.max(pos, e);
      prev = tok;
    }
    if (pos < le) out.push(<span key="tail">{decoder.decode(prep.bytes.subarray(pos, le))}</span>);
    return out;
  };

  const hoverTok = hover ? tokens[hover.i] : null;
  const hoverPh = hoverTok && hoverTok.ph !== null ? phrases[hoverTok.ph] : null;
  const total = tokens.length || 1;

  return (
    <div className="flex gap-4" style={{ minWidth: 980 }}>
      <div className="panel min-w-0 flex-1 overflow-hidden">
        <div className="flex flex-wrap items-center justify-between gap-3 border-b px-3 py-2" style={{ borderColor: "var(--border)" }}>
          <div className="flex flex-wrap gap-4">
            <Toggle label="Show phrases" checked={showPhrases} onChange={setShowPhrases} />
            <Toggle label="Only misses" checked={onlyMisses} onChange={setOnlyMisses} />
            <Toggle label="Dim fallback" checked={dimFallback} onChange={setDimFallback} />
          </div>
          <OutcomeLegend only={["commit", "partial", "miss", "fallback"]} />
        </div>
        <div className="flex flex-wrap gap-x-4 gap-y-1 border-b px-3 py-1.5 text-xs muted" style={{ borderColor: "var(--border)" }}>
          <span>Phrase bands:</span>
          {["copy", "static_o2", "static_o1"].map((s) => (
            <span key={s} className="inline-flex items-center gap-1.5">
              <span className="inline-block h-0.5 w-4" style={{ background: SOURCE_COLORS[s] }} />
              {SOURCE_LABELS[s]}
            </span>
          ))}
          {highlight && (
            <button className="ml-auto underline" onClick={() => setHighlight(null)}>
              Clear highlight
            </button>
          )}
        </div>
        <div
          ref={scroller}
          onScroll={(e) => setScrollTop(e.currentTarget.scrollTop)}
          className="overflow-auto font-mono text-[12.5px]"
          style={{ height: "calc(100vh - 260px)", minHeight: 420 }}
        >
          <div style={{ height: nLines * LINE_H, position: "relative" }}>
            <div style={{ position: "absolute", top: first * LINE_H, left: 0, right: 0 }}>
              {Array.from({ length: last - first }, (_, k) => {
                const l = first + k;
                return (
                  <div key={l} className="flex whitespace-pre" style={{ height: LINE_H, lineHeight: `${LINE_H}px` }}>
                    <span className="sticky left-0 shrink-0 select-none pr-3 text-right muted" style={{ width: `${gutter + 3}ch`, background: "var(--panel)" }}>
                      {l + 1}
                    </span>
                    <span>{renderLine(l)}</span>
                  </div>
                );
              })}
            </div>
          </div>
        </div>
      </div>

      <aside className="w-80 shrink-0 space-y-3">
        <div className="panel p-4">
          <div className="font-mono text-xs muted">{trace.path ?? trace.name}</div>
          <div className="mt-3 grid grid-cols-3 gap-2 text-center">
            <Stat label="Coverage" value={pct(prep.committed / total, 1)} color={COLORS.commit} />
            <Stat label="Tokens/phrase" value={tpp.toFixed(2)} />
            <Stat label="Failed probes" value={misses.toLocaleString()} color={COLORS.miss} />
          </div>
          <div className="mt-4 flex h-3 overflow-hidden rounded" title="Share of tokens by outcome">
            {(["commit", "partial", "miss", "fallback"] as Outcome[]).map((o) => (
              <div key={o} style={{ width: `${(prep.counts[o] / total) * 100}%`, background: COLORS[o] }} />
            ))}
          </div>
          <div className="mt-2 grid grid-cols-2 gap-x-3 text-xs tabular-nums">
            {(["commit", "partial", "miss", "fallback"] as Outcome[]).map((o) => (
              <div key={o} className="flex justify-between">
                <span className="muted">{o}</span>
                <span>{prep.counts[o].toLocaleString()}</span>
              </div>
            ))}
          </div>
          <p className="mt-3 text-[11px] muted">
            {tokens.length.toLocaleString()} tokens · {prep.bytes.length.toLocaleString()} bytes · source traces/{trace.name}.json
          </p>
        </div>
        <div className="panel p-4">
          <h3 className="text-sm font-semibold">Most frequent committed phrases</h3>
          <p className="text-[11px] muted">Click to highlight every occurrence</p>
          <ol className="mt-2 max-h-[46vh] space-y-1 overflow-auto">
            {prep.topPhrases.map((p) => {
              const active = highlight && p.ids.every((id) => highlight.has(id));
              return (
                <li key={p.text}>
                  <button
                    className="flex w-full items-center gap-2 rounded px-1.5 py-1 text-left text-xs"
                    style={{ background: active ? "var(--panel-2)" : undefined }}
                    onClick={() => setHighlight(active ? null : new Set(p.ids))}
                  >
                    <span className="h-3 w-1 shrink-0 rounded" style={{ background: SOURCE_COLORS[p.src] ?? COLORS.accent }} />
                    <span className="min-w-0 flex-1 truncate font-mono">{p.text}</span>
                    <span className="shrink-0 tabular-nums muted">×{p.count}</span>
                  </button>
                </li>
              );
            })}
            {!prep.topPhrases.length && <li className="text-xs muted">No committed phrases.</li>}
          </ol>
        </div>
      </aside>

      {hoverTok && hover && (
        <div
          className="panel pointer-events-none fixed z-50 w-72 p-3 text-xs shadow-lg"
          style={{ left: Math.min(hover.x + 14, window.innerWidth - 300), top: Math.min(hover.y + 14, window.innerHeight - 240) }}
        >
          <div className="mb-1.5 flex items-center gap-2">
            <span className="inline-block h-2.5 w-2.5 rounded-sm" style={{ background: COLORS[hoverTok.o] }} />
            <span className="font-semibold">{OUTCOME_LABEL[hoverTok.o]}</span>
          </div>
          <Row k="Kind" v={hoverTok.k} />
          <Row k="Bytes" v={`${hoverTok.s}–${hoverTok.e} (${hoverTok.e - hoverTok.s} B)`} />
          {hoverPh && (
            <>
              <Row k="Phrase" v={`#${hoverPh.id}`} />
              <Row k="Predictor" v={SOURCE_LABELS[hoverPh.src] ?? hoverPh.src} />
              <Row k="Confidence" v={`${hoverPh.conf} / 3`} />
              <Row k="Phrase length" v={`${hoverPh.ntok} tokens, ${hoverPh.e - hoverPh.s} B, ${hoverPh.accepted} accepted`} />
              {hoverPh.mismatch_at !== null && <Row k="Mismatch at" v={`byte ${hoverPh.mismatch_at} of phrase`} />}
              {hoverPh.accepted === 0 && hoverPh.mismatch_at !== null && (
                <Row k="Expected / actual" v={`${byteChar(hoverPh.expected)} / ${byteChar(hoverPh.actual)}`} />
              )}
              {hoverPh.accepted === 0 && hoverPh.mismatch_at === null && (
                <Row k="Rejected by" v="guard byte (bytes matched)" />
              )}
            </>
          )}
        </div>
      )}
    </div>
  );
}

function Stat({ label, value, color }: { label: string; value: string; color?: string }) {
  return (
    <div>
      <div className="text-lg font-semibold tabular-nums" style={color ? { color } : undefined}>{value}</div>
      <div className="text-[11px] muted">{label}</div>
    </div>
  );
}

function Row({ k, v }: { k: string; v: string }) {
  return (
    <div className="flex justify-between gap-3 py-0.5">
      <span className="muted">{k}</span>
      <span className="text-right font-mono">{v}</span>
    </div>
  );
}
