import { useEffect, useState } from "react";
import { NavLink, Outlet } from "react-router-dom";
import { datasetMeta, useData } from "./data";

const NAV = [
  { to: "/", label: "Overview" },
  { to: "/limit-study", label: "Limit Study" },
  { to: "/benchmarks", label: "Benchmarks" },
  { to: "/inspector", label: "Token Inspector" },
  { to: "/cost-model", label: "Cost Model" },
];

type Theme = "light" | "dark";

function initialTheme(): Theme {
  try {
    const t = localStorage.getItem("plab-theme");
    if (t === "light" || t === "dark") return t;
  } catch {
    /* storage unavailable */
  }
  return window.matchMedia?.("(prefers-color-scheme: dark)").matches ? "dark" : "light";
}

export default function Layout() {
  const [theme, setTheme] = useState<Theme>(initialTheme);
  const data = useData();
  const { meta, sample } = datasetMeta(data);

  useEffect(() => {
    document.documentElement.classList.toggle("dark", theme === "dark");
    try {
      localStorage.setItem("plab-theme", theme);
    } catch {
      /* storage unavailable */
    }
  }, [theme]);

  return (
    <div className="flex min-h-screen">
      <aside className="sticky top-0 flex h-screen w-52 shrink-0 flex-col border-r px-3 py-5" style={{ borderColor: "var(--border)", background: "var(--panel)" }}>
        <div className="mb-6 px-2">
          <div className="text-base font-semibold tracking-tight">PLAB</div>
          <div className="text-[11px] muted leading-tight">Predictive Lexical Analysis Buffering</div>
        </div>
        <nav className="flex flex-col gap-0.5">
          {NAV.map((n) => (
            <NavLink
              key={n.to}
              to={n.to}
              end={n.to === "/"}
              className="rounded-md px-2 py-1.5 text-sm"
              style={({ isActive }) =>
                isActive
                  ? { background: "var(--panel-2)", color: "var(--text)", fontWeight: 600 }
                  : { color: "var(--muted)" }
              }
            >
              {n.label}
            </NavLink>
          ))}
        </nav>
        <div className="mt-auto px-2">
          <button
            onClick={() => setTheme(theme === "dark" ? "light" : "dark")}
            className="w-full rounded-md border px-2 py-1.5 text-xs"
            style={{ borderColor: "var(--border)" }}
          >
            {theme === "dark" ? "Light theme" : "Dark theme"}
          </button>
        </div>
      </aside>
      <div className="flex min-w-0 flex-1 flex-col">
        <div className="flex flex-wrap items-center gap-x-5 gap-y-1 border-b px-6 py-2.5 text-xs" style={{ borderColor: "var(--border)", background: "var(--panel)" }}>
          {sample && (
            <span className="rounded px-1.5 py-0.5 font-semibold" style={{ background: "var(--c-miss-bg)", color: "var(--c-miss)" }}>
              sample data
            </span>
          )}
          {meta ? (
            <>
              <span><span className="muted">Machine</span> {meta.machine}</span>
              <span className="truncate"><span className="muted">CPU</span> {meta.cpu}</span>
              <span><span className="muted">Commit</span> {meta.commit}</span>
              <span><span className="muted">Date</span> {meta.date}</span>
              <span className="truncate"><span className="muted">Compiler</span> {meta.compiler}</span>
            </>
          ) : (
            <span className="muted">No dataset loaded</span>
          )}
        </div>
        <main className="min-w-0 flex-1 px-6 py-6">
          <Outlet />
        </main>
      </div>
    </div>
  );
}
