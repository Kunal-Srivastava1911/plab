import {
  Bar,
  BarChart,
  CartesianGrid,
  Cell,
  ErrorBar,
  ReferenceLine,
  ResponsiveContainer,
  Tooltip,
  XAxis,
  YAxis,
} from "recharts";
import { COLORS, ChartCard, Empty, PageHeader, SwatchLegend, WithData, axisProps, tooltipProps } from "../components";
import { pct, useData } from "../data";
import type { Bench, BenchRow } from "../types";

const SRC = "results/bench.json";
const ABLATION_LABEL: Record<string, string> = {
  spec_predictors: "Spec predictors (order-2 copy, conf ≥ 2)",
  copy_only: "Copy only",
  static_only: "Static only",
  kind_only_contexts: "Kind-only contexts",
  no_partial: "No partial acceptance",
  no_guard_classes: "Exact guard bytes only",
  no_intern_cache: "No intern-ID caching",
  no_prefetch: "No successor prefetch",
  governor_off: "Governor off",
  W16: "W = 16",
};

const nm = (v: number | null, digits = 2) => (v === null ? "not measured" : v.toFixed(digits));

export default function Benchmarks() {
  const { bench } = useData();
  return (
    <div className="max-w-6xl">
      <PageHeader
        title="Benchmarks"
        sub="Throughput of the hand-written direct-coded baseline (re2c-style; re2c itself was not available) alone and with PLAB in front. PLAB's governor measures both modes and runs the cheaper one per 4 KB window. Medians of interleaved runs on a pinned core, whiskers are 95% confidence intervals."
      />
      <WithData load={bench} what="benchmarks">
        {(d) => <Body d={d} />}
      </WithData>
    </div>
  );
}

function pair(rows: BenchRow[], corpus: string, project: string) {
  const base = rows.find((r) => r.corpus === corpus && r.project === project && !r.plab);
  const plab = rows.find((r) => r.corpus === corpus && r.project === project && r.plab && r.config === "default");
  return base && plab ? { base, plab, speedup: plab.mb_s.median / base.mb_s.median } : null;
}

function Body({ d }: { d: Bench }) {
  const rows = d.rows;
  const projects = [...new Set(rows.filter((r) => r.corpus === "test" && r.project !== "all").map((r) => r.project))];
  if (!projects.length) return <Empty message="bench.json has no test-corpus rows." />;
  const pairs = projects
    .map((p) => ({ project: p, pr: pair(rows, "test", p) }))
    .filter((x): x is { project: string; pr: NonNullable<ReturnType<typeof pair>> } => x.pr !== null);

  const tput = pairs.map(({ project, pr }) => ({
    project,
    baseline: pr.base.mb_s.median,
    plab: pr.plab.mb_s.median,
    baseErr: [pr.base.mb_s.median - pr.base.mb_s.ci95[0], pr.base.mb_s.ci95[1] - pr.base.mb_s.median],
    plabErr: [pr.plab.mb_s.median - pr.plab.mb_s.ci95[0], pr.plab.mb_s.ci95[1] - pr.plab.mb_s.median],
  }));
  const speed = pairs.map(({ project, pr }) => ({ project, speedup: pr.speedup, coverage: pr.plab.coverage_tokens }));
  const all = pair(rows, "test", "all");
  const best = speed.reduce((m, s) => (s.speedup > m.speedup ? s : m), speed[0]);

  const adv = [...new Set(rows.filter((r) => r.corpus === "adversarial").map((r) => r.project))]
    .map((p) => ({ p, pr: pair(rows, "adversarial", p) }))
    .filter((x): x is { p: string; pr: NonNullable<ReturnType<typeof pair>> } => x.pr !== null)
    .map(({ p, pr }) => ({ input: p, slowdown: 1 - pr.speedup, coverage: pr.plab.coverage_tokens }));
  const worst = adv.reduce((m, a) => (a.slowdown > m.slowdown ? a : m), adv[0] ?? { input: "", slowdown: 0, coverage: 0 });

  const def = rows.find((r) => r.corpus === "test" && r.project === "all" && r.config === "default");
  const abl = rows
    .filter((r) => r.corpus === "test" && r.project === "all" && r.plab && r.config !== "default")
    .map((r) => ({
      name: ABLATION_LABEL[r.config] ?? r.config,
      vsDefault: def ? r.mb_s.median / def.mb_s.median : 0,
      coverage: r.coverage_tokens,
    }))
    .sort((a, b) => b.vsDefault - a.vsDefault);
  const bestAbl = abl[0];

  return (
    <div className="grid gap-4 lg:grid-cols-2">
      <ChartCard
        className="lg:col-span-2"
        title={`PLAB is faster than the direct-coded baseline on ${speed.filter((s) => s.speedup > 1).length} of ${speed.length} test projects${all ? ` (${all.speedup.toFixed(2)}× overall)` : ""}`}
        source={SRC}
        legend={
          <SwatchLegend
            items={[
              { color: COLORS.fallback, label: "Baseline alone" },
              { color: COLORS.accent, label: "PLAB over baseline" },
            ]}
          />
        }
      >
        <ResponsiveContainer width="100%" height={280}>
          <BarChart data={tput} margin={{ top: 8, right: 8, left: 4, bottom: 0 }} barGap={4}>
            <CartesianGrid stroke={COLORS.grid} vertical={false} />
            <XAxis dataKey="project" {...axisProps} />
            <YAxis width={56} label={{ value: "Throughput (MB/s)", angle: -90, position: "insideLeft", fill: "var(--muted)", fontSize: 12 }} {...axisProps} />
            <Tooltip {...tooltipProps} formatter={(v: number, n: string) => [`${v.toFixed(1)} MB/s`, n === "plab" ? "PLAB" : "Baseline"]} />
            <Bar dataKey="baseline" fill={COLORS.fallback} radius={[3, 3, 0, 0]} isAnimationActive={false}>
              <ErrorBar dataKey="baseErr" width={6} stroke="var(--text)" />
            </Bar>
            <Bar dataKey="plab" fill={COLORS.accent} radius={[3, 3, 0, 0]} isAnimationActive={false}>
              <ErrorBar dataKey="plabErr" width={6} stroke="var(--text)" />
            </Bar>
          </BarChart>
        </ResponsiveContainer>
      </ChartCard>

      <ChartCard
        title={`Best project ratio is ${best.speedup.toFixed(2)}× (${best.project}); target ≥ 1.5×`}
        source={SRC}
      >
        <ResponsiveContainer width="100%" height={240}>
          <BarChart data={speed} margin={{ top: 8, right: 8, left: 4, bottom: 0 }}>
            <CartesianGrid stroke={COLORS.grid} vertical={false} />
            <XAxis dataKey="project" {...axisProps} />
            <YAxis domain={[0, (max: number) => Math.max(1.2, Math.ceil(max * 10) / 10)]} tickFormatter={(v) => `${v}×`} width={44} {...axisProps} />
            <Tooltip {...tooltipProps} formatter={(v: number) => [`${v.toFixed(3)}×`, "PLAB / baseline"]} />
            <ReferenceLine y={1} stroke="var(--text)" strokeDasharray="4 3" label={{ value: "1.0×", position: "right", fill: "var(--muted)", fontSize: 11 }} />
            <Bar dataKey="speedup" radius={[3, 3, 0, 0]} isAnimationActive={false}>
              {speed.map((s) => (
                <Cell key={s.project} fill={s.speedup >= 1 ? COLORS.commit : COLORS.miss} />
              ))}
            </Bar>
          </BarChart>
        </ResponsiveContainer>
      </ChartCard>

      <ChartCard
        title={`Worst adversarial slowdown is ${pct(Math.max(0, worst.slowdown), 1)} (${worst.input}); target ≤ 5%`}
        source={SRC}
        legend={<SwatchLegend items={[{ color: COLORS.bad, label: "5% slowdown limit", dashed: true }]} />}
      >
        {adv.length ? (
          <ResponsiveContainer width="100%" height={240}>
            <BarChart data={adv} margin={{ top: 8, right: 8, left: 4, bottom: 0 }}>
              <CartesianGrid stroke={COLORS.grid} vertical={false} />
              <XAxis dataKey="input" {...axisProps} />
              <YAxis tickFormatter={(v) => pct(v)} width={44} label={{ value: "Slowdown", angle: -90, position: "insideLeft", fill: "var(--muted)", fontSize: 12 }} {...axisProps} />
              <Tooltip
                {...tooltipProps}
                formatter={(v: number, n: string) => [pct(v, 1), n === "slowdown" ? "Slowdown vs baseline" : n]}
              />
              <ReferenceLine y={0.05} stroke={COLORS.bad} strokeDasharray="5 4" />
              <ReferenceLine y={0} stroke="var(--border)" />
              <Bar dataKey="slowdown" radius={[3, 3, 0, 0]} isAnimationActive={false}>
                {adv.map((a) => (
                  <Cell key={a.input} fill={a.slowdown > 0.05 ? COLORS.bad : COLORS.miss} />
                ))}
              </Bar>
            </BarChart>
          </ResponsiveContainer>
        ) : (
          <Empty message="No adversarial rows in bench.json." />
        )}
      </ChartCard>

      <ChartCard
        className="lg:col-span-2"
        title={
          bestAbl
            ? `${bestAbl.name} is the fastest variant at ${bestAbl.vsDefault.toFixed(2)}× the default configuration`
            : "Ablations"
        }
        source={SRC}
      >
        {abl.length ? (
          <ResponsiveContainer width="100%" height={320}>
            <BarChart data={abl} layout="vertical" margin={{ top: 4, right: 40, left: 8, bottom: 4 }}>
              <CartesianGrid stroke={COLORS.grid} horizontal={false} />
              <XAxis type="number" tickFormatter={(v) => `${v}×`} domain={[0, "auto"]} {...axisProps} />
              <YAxis type="category" dataKey="name" width={230} {...axisProps} />
              <Tooltip
                {...tooltipProps}
                formatter={(v: number, n: string) => (n === "vsDefault" ? [`${v.toFixed(3)}×`, "Throughput vs default"] : [pct(v, 1), "Coverage"])}
              />
              <ReferenceLine x={1} stroke="var(--text)" strokeDasharray="4 3" />
              <Bar dataKey="vsDefault" fill={COLORS.accent} radius={[0, 3, 3, 0]} isAnimationActive={false} />
            </BarChart>
          </ResponsiveContainer>
        ) : (
          <Empty message="No ablation rows in bench.json." />
        )}
        <p className="text-[11px] muted">All test-corpus files. Throughput of each ablation relative to the default PLAB configuration (1.0×).</p>
      </ChartCard>

      <section className="panel p-4 lg:col-span-2">
        <h2 className="text-sm font-semibold">Cycles per byte per project; hardware counters were not measured on Windows</h2>
        <div className="mt-3 overflow-x-auto">
          <table className="w-full text-sm tabular-nums">
            <thead>
              <tr className="text-left text-xs muted">
                {["Project", "Config", "MB/s", "M tokens/s", "Cycles/byte", "Instr/byte", "Mispredicts/token", "L1D misses/KB", "Coverage"].map((h, i) => (
                  <th key={h} className={`py-1.5 font-medium ${i > 1 ? "text-right" : ""}`}>{h}</th>
                ))}
              </tr>
            </thead>
            <tbody>
              {rows
                .filter((r) => r.corpus === "test" && (r.config === "default" || r.config === "baseline"))
                .map((r) => (
                  <tr key={`${r.project}-${r.config}`} className="border-t" style={{ borderColor: "var(--border)" }}>
                    <td className="py-1.5">{r.project}</td>
                    <td className="py-1.5">{r.plab ? "PLAB" : "Baseline"}</td>
                    <td className="py-1.5 text-right">{r.mb_s.median.toFixed(1)}</td>
                    <td className="py-1.5 text-right">{r.mtok_s.median.toFixed(1)}</td>
                    <td className="py-1.5 text-right">{r.cycles_per_byte.toFixed(2)}</td>
                    <td className="py-1.5 text-right muted">{nm(r.instr_per_byte)}</td>
                    <td className="py-1.5 text-right muted">{nm(r.branch_miss_per_tok)}</td>
                    <td className="py-1.5 text-right muted">{nm(r.l1d_miss_per_kb)}</td>
                    <td className="py-1.5 text-right">{r.plab ? pct(r.coverage_tokens, 1) : "–"}</td>
                  </tr>
                ))}
            </tbody>
          </table>
        </div>
        <p className="mt-2 text-[11px] muted">
          Cycles are TSC reference cycles. Source: {SRC}
        </p>
      </section>
    </div>
  );
}
