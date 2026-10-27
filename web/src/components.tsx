import type { ReactNode } from "react";
import type { Load } from "./data";

export const COLORS = {
  commit: "var(--c-commit)",
  partial: "var(--c-partial)",
  miss: "var(--c-miss)",
  fallback: "var(--c-fallback)",
  accent: "var(--c-accent)",
  bad: "var(--c-bad)",
  grid: "var(--grid)",
  muted: "var(--muted)",
};

export const SOURCE_COLORS: Record<string, string> = {
  copy: "var(--c-src-copy)",
  static_o2: "var(--c-src-o2)",
  static_o3: "var(--c-src-o2)",
  static_o1: "var(--c-src-o1)",
};

export const SOURCE_LABELS: Record<string, string> = {
  copy: "Copy predictor",
  static_o2: "Static order-2",
  static_o3: "Static order-3",
  static_o1: "Static order-1",
};

const OUTCOME_ITEMS = [
  ["commit", "Committed"],
  ["partial", "Partial"],
  ["miss", "Failed probe"],
  ["fallback", "Fallback"],
] as const;

/* Fixed color meaning used on every page (spec 10). */
export function OutcomeLegend({ only }: { only?: (keyof typeof COLORS)[] }) {
  const items = OUTCOME_ITEMS.filter(([k]) => !only || only.includes(k));
  return (
    <div className="flex flex-wrap items-center gap-x-4 gap-y-1 text-xs muted">
      {items.map(([k, label]) => (
        <span key={k} className="inline-flex items-center gap-1.5">
          <span className="inline-block h-2.5 w-2.5 rounded-sm" style={{ background: COLORS[k] }} />
          {label}
        </span>
      ))}
    </div>
  );
}

export function SwatchLegend({ items }: { items: { color: string; label: string; dashed?: boolean }[] }) {
  return (
    <div className="flex flex-wrap items-center gap-x-4 gap-y-1 text-xs muted">
      {items.map((it) => (
        <span key={it.label} className="inline-flex items-center gap-1.5">
          <span
            className="inline-block h-0.5 w-4"
            style={{ borderTop: `2px ${it.dashed ? "dashed" : "solid"} ${it.color}` }}
          />
          {it.label}
        </span>
      ))}
    </div>
  );
}

export function PageHeader({ title, sub }: { title: string; sub?: ReactNode }) {
  return (
    <header className="mb-5">
      <h1 className="text-xl font-semibold tracking-tight">{title}</h1>
      {sub && <p className="mt-1 text-sm muted max-w-3xl">{sub}</p>}
    </header>
  );
}

/* Every chart: a title stating the finding, units, and the source JSON file. */
export function ChartCard({
  title,
  source,
  legend,
  children,
  right,
  className = "",
}: {
  title: string;
  source: string;
  legend?: ReactNode;
  children: ReactNode;
  right?: ReactNode;
  className?: string;
}) {
  return (
    <section className={`panel p-4 ${className}`}>
      <div className="mb-2 flex items-start justify-between gap-3">
        <h2 className="text-sm font-semibold leading-snug">{title}</h2>
        {right}
      </div>
      {legend && <div className="mb-2">{legend}</div>}
      {children}
      <p className="mt-2 text-[11px] muted">Source: {source}</p>
    </section>
  );
}

export function Kpi({ label, value, note, tone }: { label: string; value: string; note?: string; tone?: string }) {
  return (
    <div className="panel p-4">
      <div className="text-xs muted">{label}</div>
      <div className="mt-1 text-2xl font-semibold tabular-nums" style={tone ? { color: tone } : undefined}>
        {value}
      </div>
      {note && <div className="mt-1 text-xs muted">{note}</div>}
    </div>
  );
}

export function Loading({ what }: { what: string }) {
  return <div className="panel p-6 text-sm muted animate-pulse">Loading {what}…</div>;
}

export function ErrorBox({ message }: { message: string }) {
  return (
    <div className="panel p-6 text-sm" style={{ borderColor: "var(--c-bad)" }}>
      <div className="font-semibold" style={{ color: "var(--c-bad)" }}>
        Data missing
      </div>
      <div className="mt-1 muted">{message}</div>
    </div>
  );
}

export function Empty({ message }: { message: string }) {
  return <div className="panel p-6 text-sm muted">{message}</div>;
}

/* Render loading / error states for a result, or the page body. */
export function WithData<T>({ load, what, children }: { load: Load<T>; what: string; children: (d: T) => ReactNode }) {
  if (load.state === "loading") return <Loading what={what} />;
  if (load.state === "error") return <ErrorBox message={load.message} />;
  return <>{children(load.data)}</>;
}

export function Toggle({ label, checked, onChange }: { label: string; checked: boolean; onChange: (v: boolean) => void }) {
  return (
    <label className="inline-flex cursor-pointer items-center gap-2 text-sm select-none">
      <input type="checkbox" className="accent-blue-600" checked={checked} onChange={(e) => onChange(e.target.checked)} />
      {label}
    </label>
  );
}

export function Segmented<T extends string>({
  value,
  options,
  onChange,
}: {
  value: T;
  options: { value: T; label: string }[];
  onChange: (v: T) => void;
}) {
  return (
    <div className="inline-flex rounded-lg border p-0.5" style={{ borderColor: "var(--border)", background: "var(--panel-2)" }}>
      {options.map((o) => (
        <button
          key={o.value}
          onClick={() => onChange(o.value)}
          className="rounded-md px-2.5 py-1 text-xs font-medium"
          style={
            o.value === value
              ? { background: "var(--panel)", color: "var(--text)", boxShadow: "0 1px 2px rgba(0,0,0,.08)" }
              : { color: "var(--muted)" }
          }
        >
          {o.label}
        </button>
      ))}
    </div>
  );
}

export const axisProps = {
  stroke: "var(--border)",
  tick: { fill: "var(--muted)", fontSize: 12 },
  tickLine: false,
} as const;

export const tooltipProps = {
  contentStyle: {
    background: "var(--panel)",
    border: "1px solid var(--border)",
    borderRadius: 8,
    fontSize: 12,
    color: "var(--text)",
  },
  labelStyle: { color: "var(--text)", fontWeight: 600 },
  itemStyle: { color: "var(--text)" },
  cursor: { fill: "var(--panel-2)" },
} as const;
