import { COLORS, ErrorBox, Kpi, Loading, OutcomeLegend, PageHeader } from "../components";
import { pct, useData } from "../data";
import type { BenchRow, LimitRun } from "../types";

export const isDefaultRun = (r: LimitRun) => r.budget_kb === 512 && r.order === 2 && r.W === 32;
const PREDICTORS = ["cascade", "both", "copy", "static", "markov_kind"];
const PRED_LABEL: Record<string, string> = {
  cascade: "Cascade copy + static",
  both: "Copy + static (spec)",
  copy: "Copy only",
  static: "Static only",
  markov_kind: "Kind-only Markov",
};
const LANG_LABEL: Record<string, string> = { c: "C", python: "Python" };

export function speedupOf(rows: BenchRow[], corpus: string, project: string): number | null {
  const base = rows.find((r) => r.corpus === corpus && r.project === project && !r.plab);
  const p = rows.find((r) => r.corpus === corpus && r.project === project && r.plab && r.config === "default");
  return base && p ? p.mb_s.median / base.mb_s.median : null;
}

export default function Overview() {
  const { limit, bench, difftest } = useData();
  if (limit.state === "loading" || bench.state === "loading" || difftest.state === "loading")
    return <Loading what="results" />;

  const runs = limit.state === "ok" ? limit.data.runs.filter(isDefaultRun) : [];
  const both = (lang: string) =>
    runs.find((r) => r.lang === lang && r.predictor === "cascade") ?? runs.find((r) => r.lang === lang && r.predictor === "both");
  const c = both("c");
  const py = both("python");

  const rows = bench.state === "ok" ? bench.data.rows : [];
  const testProjects = [...new Set(rows.filter((r) => r.corpus === "test" && r.project !== "all").map((r) => r.project))];
  const advProjects = [...new Set(rows.filter((r) => r.corpus === "adversarial").map((r) => r.project))];
  const best = testProjects
    .map((p) => ({ p, s: speedupOf(rows, "test", p) }))
    .filter((x): x is { p: string; s: number } => x.s !== null)
    .sort((a, b) => b.s - a.s)[0];
  const worstAdv = advProjects
    .map((p) => ({ p, s: speedupOf(rows, "adversarial", p) }))
    .filter((x): x is { p: string; s: number } => x.s !== null)
    .sort((a, b) => a.s - b.s)[0];
  const allSpeed = speedupOf(rows, "test", "all");

  let finding = "Run the limit study to generate a finding.";
  if (c) {
    finding = `PLAB commits ${pct(c.coverage_tokens)} of C tokens through prediction in the limit study, ${c.mean_tokens_per_phrase.toFixed(1)} tokens per phrase`;
    if (allSpeed !== null)
      finding += `; on the C test corpus the measured throughput is ${allSpeed.toFixed(2)}× the direct-coded baseline`;
    finding += ".";
  }

  return (
    <div className="max-w-6xl">
      <PageHeader
        title="Overview"
        sub="PLAB predicts the next phrase of tokens from the last two, verifies it with one 32-byte compare, and commits every matching token at once."
      />
      <p className="panel mb-5 px-4 py-3 text-[15px] font-medium" style={{ borderLeft: `3px solid ${COLORS.accent}` }}>
        {finding}
      </p>

      <div className="grid grid-cols-2 gap-3 lg:grid-cols-5">
        <Kpi
          label="Token coverage (limit study)"
          value={c ? pct(c.coverage_tokens) : "–"}
          note={py ? `C · Python ${pct(py.coverage_tokens)} · target ≥ 50%` : "C"}
          tone={COLORS.commit}
        />
        <Kpi
          label="Mean tokens per phrase"
          value={c ? c.mean_tokens_per_phrase.toFixed(2) : "–"}
          note={py ? `C · Python ${py.mean_tokens_per_phrase.toFixed(2)} · target ≥ 3` : "C"}
        />
        <Kpi
          label="Best speedup vs direct-coded"
          value={best ? `${best.s.toFixed(2)}×` : "–"}
          note={best ? `${best.p} · target ≥ 1.5×` : "no benchmark"}
          tone={best && best.s >= 1 ? COLORS.commit : COLORS.miss}
        />
        <Kpi
          label="Adversarial worst-case slowdown"
          value={worstAdv ? pct(Math.max(0, 1 - worstAdv.s)) : "–"}
          note={worstAdv ? `${worstAdv.p} · target ≤ 5%` : "no benchmark"}
          tone={worstAdv && 1 - worstAdv.s > 0.05 ? COLORS.bad : COLORS.commit}
        />
        <Kpi
          label="Exactness"
          value={difftest.state === "ok" ? `${difftest.data.divergences} divergences` : "–"}
          note={difftest.state === "ok" ? `${difftest.data.files.toLocaleString()} files, every configuration` : "difftest missing"}
          tone={difftest.state === "ok" && difftest.data.divergences === 0 ? COLORS.commit : COLORS.bad}
        />
      </div>

      {limit.state === "error" ? (
        <div className="mt-5"><ErrorBox message={limit.message} /></div>
      ) : (
        <section className="panel mt-5 p-4">
          <h2 className="text-sm font-semibold">The cascade copy predictor covers the most tokens in both languages</h2>
          <p className="mt-0.5 text-xs muted">Token coverage at 512 KB static budget, order-2 contexts, W = 32</p>
          <table className="mt-3 w-full text-sm tabular-nums">
            <thead>
              <tr className="text-left text-xs muted">
                <th className="py-1.5 font-medium">Language</th>
                {PREDICTORS.map((p) => (
                  <th key={p} className="py-1.5 text-right font-medium">{PRED_LABEL[p]}</th>
                ))}
                <th className="py-1.5 text-right font-medium">Acceptance</th>
              </tr>
            </thead>
            <tbody>
              {["c", "python"].map((lang) => (
                <tr key={lang} className="border-t" style={{ borderColor: "var(--border)" }}>
                  <td className="py-1.5">{LANG_LABEL[lang]}</td>
                  {PREDICTORS.map((p) => {
                    const r = runs.find((x) => x.lang === lang && x.predictor === p);
                    return (
                      <td key={p} className="py-1.5 text-right">{r ? pct(r.coverage_tokens, 1) : "–"}</td>
                    );
                  })}
                  <td className="py-1.5 text-right muted">
                    {runs.find((x) => x.lang === lang)?.acceptance === "oracle" ? "token oracle" : "guard rule"}
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
          <div className="mt-3 flex items-center justify-between">
            <OutcomeLegend only={["commit"]} />
            <span className="text-[11px] muted">Source: results/limit_study.json</span>
          </div>
        </section>
      )}
      {bench.state === "error" && <div className="mt-5"><ErrorBox message={bench.message} /></div>}
    </div>
  );
}
