import { useState } from "react";
import {
  Bar,
  BarChart,
  CartesianGrid,
  Legend,
  Line,
  LineChart,
  ReferenceLine,
  ResponsiveContainer,
  Tooltip,
  XAxis,
  YAxis,
} from "recharts";
import {
  COLORS,
  ChartCard,
  Empty,
  PageHeader,
  SOURCE_COLORS,
  SOURCE_LABELS,
  Segmented,
  SwatchLegend,
  WithData,
  axisProps,
  tooltipProps,
} from "../components";
import { BASELINE_PRESETS, DEFAULT_COST, breakEven } from "../costmodel";
import { pct, useData } from "../data";
import type { LimitStudy as LS } from "../types";
import { isDefaultRun } from "./Overview";

const SRC = "results/limit_study.json";
const PRED_COLORS: Record<string, string> = { cascade: COLORS.commit, both: COLORS.accent, copy: "var(--c-src-copy)", static: "var(--c-src-o2)" };
const PRED_LABEL: Record<string, string> = { cascade: "Cascade copy + static", both: "Copy + static (spec)", copy: "Copy only", static: "Static only" };
const pctTick = (v: number) => `${Math.round(v * 100)}%`;

export default function LimitStudy() {
  const { limit } = useData();
  return (
    <div className="max-w-6xl">
      <PageHeader
        title="Limit Study"
        sub="Phase 0: a Python simulation of the predictors of spec 5.2 over the test corpora, with tables mined from the training corpora."
      />
      <WithData load={limit} what="limit study">
        {(d) => <Body d={d} />}
      </WithData>
    </div>
  );
}

function Body({ d }: { d: LS }) {
  const [lang, setLang] = useState("c");
  const [pred, setPred] = useState("cascade");
  const runs = d.runs.filter((r) => r.lang === lang);
  if (!runs.length) return <Empty message={`No runs for ${lang}.`} />;
  const a = d.cost_model_assumptions;
  const sel = runs.find((r) => r.predictor === pred && isDefaultRun(r)) ?? runs[0];
  const both = runs.find((r) => r.predictor === "cascade" && isDefaultRun(r)) ?? runs.find((r) => r.predictor === "both" && isDefaultRun(r)) ?? sel;

  // coverage vs budget, one line per predictor config
  const budgets = [...new Set(runs.filter((r) => r.order === 2 && r.W === 32).map((r) => r.budget_kb))].sort((x, y) => x - y);
  const preds = ["cascade", "both", "static", "copy"].filter((p) => runs.some((r) => r.predictor === p));
  const budgetData = budgets.map((b) => {
    const row: Record<string, number> = { budget: b };
    for (const p of preds) {
      const r = runs.find((x) => x.predictor === p && x.budget_kb === b && x.order === 2 && x.W === 32);
      if (r) row[p] = r.coverage_tokens;
    }
    return row;
  });
  const g = both.failed_probe_rate;
  const refs = BASELINE_PRESETS.map((bp) => ({ ...bp, a: breakEven({ ...DEFAULT_COST, ...a, C_ref: bp.C_ref, g }) }));

  // order and W
  const at = (order: number, W: number) =>
    runs.find((r) => r.predictor === "both" && r.budget_kb === 512 && r.order === order && r.W === W);
  const orderData = [1, 2, 3].map((o) => ({ name: `Order ${o}`, coverage: at(o, 32)?.coverage_tokens ?? 0 }));
  const wData = [16, 32, 64].map((w) => ({ name: `W = ${w}`, coverage: at(2, w)?.coverage_tokens ?? 0 }));
  const markov = runs.find((r) => r.predictor === "markov_kind");
  const ctxData = [...orderData, ...wData, ...(markov ? [{ name: "Kind-only", coverage: markov.coverage_tokens }] : [])];

  // histogram
  const total = sel.phrase_len_hist.reduce((s, x) => s + x, 0) || 1;
  const hist = sel.phrase_len_hist.map((n, i) => ({ tokens: i + 1, share: n / total }));
  const mode = hist.reduce((m, h) => (h.share > m.share ? h : m), hist[0]);

  // commits by source, per budget for the selected predictor
  const srcKeys = [...new Set(runs.flatMap((r) => Object.keys(r.by_source)))].filter((k) =>
    runs.some((r) => r.by_source[k] > 0),
  );
  const srcData = runs
    .filter((r) => r.predictor === pred && r.order === 2 && r.W === 32)
    .sort((x, y) => x.budget_kb - y.budget_kb)
    .map((r) => ({ name: `${r.budget_kb} KB`, ...r.by_source }));
  const topSrc = srcKeys.reduce((m, k) => ((both.by_source[k] ?? 0) > (both.by_source[m] ?? 0) ? k : m), srcKeys[0]);

  const best = budgetData[budgetData.length - 1];
  const reBE = refs.find((r) => r.key === "re2c")!;

  return (
    <>
      <div className="mb-4 flex flex-wrap items-center gap-3">
        <Segmented value={lang} onChange={setLang} options={[{ value: "c", label: "C" }, { value: "python", label: "Python" }]} />
        <Segmented
          value={pred}
          onChange={setPred}
          options={preds.map((p) => ({ value: p, label: PRED_LABEL[p] }))}
        />
        <span className="text-xs muted">
          {sel.files.toLocaleString()} test files · {sel.tokens.toLocaleString()} tokens ·{" "}
          {sel.acceptance === "oracle" ? "token-oracle acceptance" : "guard-rule acceptance"}
        </span>
      </div>

      <div className="grid gap-4 lg:grid-cols-2">
        <ChartCard
          className="lg:col-span-2"
          title={`Coverage reaches ${pct(best?.[both.predictor] ?? 0)} at ${best?.budget} KB and is ${both.coverage_tokens > reBE.a ? "above" : "below"} the direct-coded break-even (${pct(reBE.a)}) at the measured g = ${g.toFixed(2)}`}
          source={SRC}
          legend={
            <SwatchLegend
              items={[
                ...preds.map((p) => ({ color: PRED_COLORS[p], label: PRED_LABEL[p] })),
                { color: COLORS.muted, label: "Break-even coverage per baseline", dashed: true },
              ]}
            />
          }
        >
          <ResponsiveContainer width="100%" height={300}>
            <LineChart data={budgetData} margin={{ top: 8, right: 110, left: 4, bottom: 8 }}>
              <CartesianGrid stroke={COLORS.grid} vertical={false} />
              <XAxis
                dataKey="budget"
                type="number"
                scale="log"
                domain={[budgets[0], budgets[budgets.length - 1]]}
                ticks={budgets}
                tickFormatter={(v) => `${v} KB`}
                label={{ value: "Static table budget (KB, log scale)", position: "insideBottom", offset: -4, fill: "var(--muted)", fontSize: 12 }}
                height={40}
                {...axisProps}
              />
              <YAxis domain={[0, 1]} tickFormatter={pctTick} width={44} label={{ value: "Token coverage", angle: -90, position: "insideLeft", fill: "var(--muted)", fontSize: 12 }} {...axisProps} />
              <Tooltip {...tooltipProps} formatter={(v: number, n: string) => [pct(v, 1), PRED_LABEL[n] ?? n]} labelFormatter={(v) => `${v} KB`} />
              {refs.map((r) => (
                <ReferenceLine
                  key={r.key}
                  y={r.a}
                  stroke={COLORS.muted}
                  strokeDasharray="4 4"
                  label={{ value: `${r.label} ${pct(r.a)}`, position: "right", fill: "var(--muted)", fontSize: 11 }}
                />
              ))}
              {preds.map((p) => (
                <Line key={p} dataKey={p} stroke={PRED_COLORS[p]} strokeWidth={2} dot={{ r: 3 }} isAnimationActive={false} />
              ))}
            </LineChart>
          </ResponsiveContainer>
        </ChartCard>

        <ChartCard
          title={`Context order and window matter less than predictor choice: ${ctxData.map((x) => pct(x.coverage)).join(" / ")}`}
          source={SRC}
        >
          <ResponsiveContainer width="100%" height={240}>
            <BarChart data={ctxData} margin={{ top: 8, right: 8, left: 4, bottom: 0 }}>
              <CartesianGrid stroke={COLORS.grid} vertical={false} />
              <XAxis dataKey="name" interval={0} {...axisProps} tick={{ fill: "var(--muted)", fontSize: 11 }} />
              <YAxis tickFormatter={pctTick} width={44} {...axisProps} />
              <Tooltip {...tooltipProps} formatter={(v: number) => [pct(v, 1), "Token coverage"]} />
              <Bar dataKey="coverage" fill={COLORS.accent} radius={[3, 3, 0, 0]} isAnimationActive={false} />
            </BarChart>
          </ResponsiveContainer>
          <p className="text-[11px] muted">Spec copy + static predictor, 512 KB. Order sweep at W = 32; W sweep at order 2.</p>
        </ChartCard>

        <ChartCard
          title={`Most accepted phrases carry ${mode.tokens} token${mode.tokens > 1 ? "s" : ""}; the mean is ${sel.mean_tokens_per_phrase.toFixed(2)} (target ≥ 3)`}
          source={SRC}
        >
          <ResponsiveContainer width="100%" height={240}>
            <BarChart data={hist} margin={{ top: 8, right: 8, left: 4, bottom: 8 }}>
              <CartesianGrid stroke={COLORS.grid} vertical={false} />
              <XAxis dataKey="tokens" label={{ value: "Accepted tokens per phrase", position: "insideBottom", offset: -4, fill: "var(--muted)", fontSize: 12 }} height={36} {...axisProps} />
              <YAxis tickFormatter={pctTick} width={44} {...axisProps} />
              <Tooltip {...tooltipProps} formatter={(v: number) => [pct(v, 1), "Share of phrases"]} labelFormatter={(v) => `${v} tokens`} />
              <Bar dataKey="share" fill={COLORS.commit} radius={[3, 3, 0, 0]} isAnimationActive={false} />
            </BarChart>
          </ResponsiveContainer>
        </ChartCard>

        <ChartCard
          className="lg:col-span-2"
          title={`${SOURCE_LABELS[topSrc] ?? topSrc} supplies ${pct(both.by_source[topSrc] ?? 0)} of committed tokens at 512 KB`}
          source={SRC}
        >
          {srcData.length ? (
            <ResponsiveContainer width="100%" height={240}>
              <BarChart data={srcData} layout="vertical" margin={{ top: 4, right: 16, left: 8, bottom: 4 }}>
                <CartesianGrid stroke={COLORS.grid} horizontal={false} />
                <XAxis type="number" domain={[0, 1]} tickFormatter={pctTick} {...axisProps} />
                <YAxis type="category" dataKey="name" width={70} {...axisProps} />
                <Tooltip {...tooltipProps} formatter={(v: number, n: string) => [pct(v, 1), SOURCE_LABELS[n] ?? n]} />
                <Legend formatter={(v: string) => SOURCE_LABELS[v] ?? v} iconType="square" wrapperStyle={{ fontSize: 12 }} />
                {srcKeys.map((k) => (
                  <Bar key={k} dataKey={k} stackId="s" fill={SOURCE_COLORS[k] ?? COLORS.fallback} isAnimationActive={false} />
                ))}
              </BarChart>
            </ResponsiveContainer>
          ) : (
            <Empty message="No source breakdown for this predictor." />
          )}
          <p className="text-[11px] muted">Share of committed tokens by predictor source, {PRED_LABEL[pred]}, per static budget.</p>
        </ChartCard>
      </div>
    </>
  );
}
