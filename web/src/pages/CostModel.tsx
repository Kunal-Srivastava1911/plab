import { useEffect, useMemo, useState } from "react";
import {
  CartesianGrid,
  Line,
  LineChart,
  ReferenceDot,
  ReferenceLine,
  ResponsiveContainer,
  Tooltip,
  XAxis,
  YAxis,
} from "recharts";
import { COLORS, ChartCard, PageHeader, SwatchLegend, axisProps, tooltipProps } from "../components";
import { BASELINE_PRESETS, DEFAULT_COST, breakEven, fallbackCost, speedup, type CostParams } from "../costmodel";
import { pct, useData } from "../data";
import { isDefaultRun } from "./Overview";

const SLIDERS: { key: keyof CostParams; label: string; min: number; max: number; step: number; unit: string }[] = [
  { key: "C_ref", label: "C_ref: baseline cost per token", min: 4, max: 60, step: 1, unit: "cycles" },
  { key: "C_hit", label: "C_hit: cost of an accepted phrase", min: 2, max: 60, step: 1, unit: "cycles" },
  { key: "n", label: "n: tokens per accepted phrase", min: 1, max: 8, step: 0.1, unit: "tokens" },
  { key: "C_ctx", label: "C_ctx: context hash per fallback token", min: 0, max: 10, step: 0.5, unit: "cycles" },
  { key: "C_p", label: "C_p: cost of a probe", min: 0, max: 40, step: 1, unit: "cycles" },
  { key: "P_br", label: "P_br: branch mispredict penalty", min: 0, max: 40, step: 1, unit: "cycles" },
  { key: "g", label: "g: fallback tokens with a failed probe", min: 0, max: 1, step: 0.01, unit: "" },
];

export default function CostModel() {
  const { limit } = useData();
  const [p, setP] = useState<CostParams>(DEFAULT_COST);
  const measured = useMemo(() => {
    if (limit.state !== "ok") return [];
    return limit.data.runs
      .filter((r) => r.predictor === "cascade" && isDefaultRun(r))
      .map((r) => ({ lang: r.lang === "c" ? "C" : "Python", a: r.coverage_tokens, g: r.failed_probe_rate, n: r.mean_tokens_per_phrase }));
  }, [limit]);

  // start from the measured C failed-probe rate once the limit study loads
  useEffect(() => {
    const c = measured.find((m) => m.lang === "C");
    if (c) setP((x) => ({ ...x, g: Math.round(c.g * 100) / 100 }));
  }, [measured]);

  const F = fallbackCost(p);
  const aStar = breakEven(p);
  const curve = useMemo(
    () => Array.from({ length: 101 }, (_, i) => ({ a: i / 100, S: speedup(p, i / 100) })),
    [p],
  );
  const sMax = Math.max(...curve.map((c) => c.S));
  const validStar = aStar >= 0 && aStar <= 1;

  return (
    <div className="max-w-6xl">
      <PageHeader
        title="Cost Model"
        sub="Section 7 of the spec: predicted speedup S(a) as a function of token coverage a. Move the sliders to see where PLAB breaks even."
      />
      <div className="grid gap-4 lg:grid-cols-[320px_1fr]">
        <section className="panel space-y-3 p-4">
          <div>
            <div className="mb-1.5 text-xs muted">Baseline preset (C_ref)</div>
            <div className="flex flex-wrap gap-1.5">
              {BASELINE_PRESETS.map((b) => (
                <button
                  key={b.key}
                  onClick={() => setP({ ...p, C_ref: b.C_ref })}
                  className="rounded-md border px-2 py-1 text-xs"
                  style={{ borderColor: p.C_ref === b.C_ref ? "var(--c-accent)" : "var(--border)" }}
                >
                  {b.label} ({b.C_ref})
                </button>
              ))}
            </div>
          </div>
          {SLIDERS.map((s) => (
            <label key={s.key} className="block">
              <div className="flex justify-between text-xs">
                <span className="muted">{s.label}</span>
                <span className="font-mono tabular-nums">
                  {p[s.key]}
                  {s.unit && ` ${s.unit}`}
                </span>
              </div>
              <input
                type="range"
                className="w-full accent-blue-600"
                min={s.min}
                max={s.max}
                step={s.step}
                value={p[s.key]}
                onChange={(e) => setP({ ...p, [s.key]: Number(e.target.value) })}
              />
            </label>
          ))}
          <button className="text-xs underline muted" onClick={() => setP(DEFAULT_COST)}>
            Reset to spec assumptions
          </button>
        </section>

        <div className="space-y-4">
          <ChartCard
            title={
              validStar
                ? `PLAB breaks even at ${pct(aStar)} coverage and reaches ${speedup(p, 1).toFixed(2)}× at full coverage`
                : "With these costs PLAB never breaks even"
            }
            source="spec section 7 formulas; measured coverage from results/limit_study.json"
            legend={
              <SwatchLegend
                items={[
                  { color: COLORS.accent, label: "Predicted speedup S(a)" },
                  { color: COLORS.commit, label: "Measured coverage (limit study)", dashed: true },
                  { color: COLORS.muted, label: "No speedup (1.0×)", dashed: true },
                ]}
              />
            }
          >
            <ResponsiveContainer width="100%" height={340}>
              <LineChart data={curve} margin={{ top: 16, right: 24, left: 4, bottom: 12 }}>
                <CartesianGrid stroke={COLORS.grid} />
                <XAxis
                  dataKey="a"
                  type="number"
                  domain={[0, 1]}
                  ticks={[0, 0.2, 0.4, 0.6, 0.8, 1]}
                  tickFormatter={(v) => pct(v)}
                  label={{ value: "Token coverage a", position: "insideBottom", offset: -6, fill: "var(--muted)", fontSize: 12 }}
                  height={40}
                  {...axisProps}
                />
                <YAxis
                  domain={[0, Math.ceil(sMax * 2) / 2]}
                  tickFormatter={(v) => `${v}×`}
                  width={44}
                  label={{ value: "Speedup S(a)", angle: -90, position: "insideLeft", fill: "var(--muted)", fontSize: 12 }}
                  {...axisProps}
                />
                <Tooltip {...tooltipProps} formatter={(v: number) => [`${v.toFixed(2)}×`, "S(a)"]} labelFormatter={(v) => `a = ${pct(Number(v))}`} />
                <ReferenceLine y={1} stroke={COLORS.muted} strokeDasharray="4 4" />
                {measured.map((m) => (
                  <ReferenceLine
                    key={m.lang}
                    x={m.a}
                    stroke={COLORS.commit}
                    strokeDasharray="5 4"
                    label={{ value: `${m.lang} ${pct(m.a)} → ${speedup(p, m.a).toFixed(2)}×`, position: "insideTopRight", fill: "var(--c-commit)", fontSize: 11 }}
                  />
                ))}
                <Line dataKey="S" stroke={COLORS.accent} strokeWidth={2.5} dot={false} isAnimationActive={false} />
                {validStar && (
                  <ReferenceDot
                    x={aStar}
                    y={1}
                    r={5}
                    fill={COLORS.accent}
                    stroke="var(--panel)"
                    label={{ value: `break-even a* = ${pct(aStar, 1)}`, position: "bottom", fill: "var(--text)", fontSize: 12 }}
                  />
                )}
              </LineChart>
            </ResponsiveContainer>
          </ChartCard>

          <section className="panel p-4 font-mono text-[13px] leading-7">
            <div>
              F = C_ctx + g·(C_p + P_br) = {p.C_ctx} + {p.g}·({p.C_p} + {p.P_br}) = <b>{F.toFixed(2)}</b> cycles
            </div>
            <div>
              S(a) = C_ref / (a·C_hit/n + (1−a)·(C_ref + F)) = {p.C_ref} / (a·{(p.C_hit / p.n).toFixed(2)} + (1−a)·{(p.C_ref + F).toFixed(2)})
            </div>
            <div>
              a* = F / (C_ref + F − C_hit/n) = {F.toFixed(2)} / ({p.C_ref} + {F.toFixed(2)} − {(p.C_hit / p.n).toFixed(2)}) ={" "}
              <b>{validStar ? pct(aStar, 1) : "n/a"}</b>
            </div>
            {measured.map((m) => (
              <div key={m.lang} className="muted">
                {m.lang}: measured a = {pct(m.a, 1)}, g = {m.g.toFixed(3)}, n = {m.n.toFixed(2)} → S = {speedup(p, m.a).toFixed(2)}×
              </div>
            ))}
          </section>
        </div>
      </div>
    </div>
  );
}
