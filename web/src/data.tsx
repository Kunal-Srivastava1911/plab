import { createContext, useContext, useEffect, useState, type ReactNode } from "react";
import type { Bench, Difftest, LimitStudy, Meta } from "./types";

export type Load<T> =
  | { state: "loading" }
  | { state: "error"; message: string }
  | { state: "ok"; data: T; sample: boolean; file: string };

/* Results come from web/public/results/ (npm run sync); the sample/ folder is only a fallback. */
async function fetchResult<T>(name: string): Promise<Load<T>> {
  for (const [dir, sample] of [["results", false], ["results/sample", true]] as const) {
    try {
      const r = await fetch(`${dir}/${name}`);
      if (!r.ok) continue;
      const text = await r.text();
      if (text.trimStart().startsWith("<")) continue; // dev server index.html fallback
      return { state: "ok", data: JSON.parse(text) as T, sample, file: `results/${name}` };
    } catch {
      /* try the next location */
    }
  }
  return { state: "error", message: `results/${name} is missing. Run the pipeline, then npm run sync.` };
}

export async function fetchJson<T>(path: string): Promise<T> {
  const r = await fetch(path);
  if (!r.ok) throw new Error(`${path}: HTTP ${r.status}`);
  return (await r.json()) as T;
}

interface Data {
  limit: Load<LimitStudy>;
  bench: Load<Bench>;
  difftest: Load<Difftest>;
}

const LOADING: Data = {
  limit: { state: "loading" },
  bench: { state: "loading" },
  difftest: { state: "loading" },
};

const Ctx = createContext<Data>(LOADING);

export function DataProvider({ children }: { children: ReactNode }) {
  const [data, setData] = useState<Data>(LOADING);
  useEffect(() => {
    void Promise.all([
      fetchResult<LimitStudy>("limit_study.json"),
      fetchResult<Bench>("bench.json"),
      fetchResult<Difftest>("difftest.json"),
    ]).then(([limit, bench, difftest]) => setData({ limit, bench, difftest }));
  }, []);
  return <Ctx.Provider value={data}>{children}</Ctx.Provider>;
}

export function useData(): Data {
  return useContext(Ctx);
}

export function datasetMeta(d: Data): { meta: Meta | null; sample: boolean } {
  for (const l of [d.bench, d.limit, d.difftest] as Load<{ meta: Meta }>[]) {
    if (l.state === "ok") {
      const sample = [d.bench, d.limit, d.difftest].some((x) => x.state === "ok" && x.sample);
      return { meta: l.data.meta, sample };
    }
  }
  return { meta: null, sample: false };
}

export const pct = (x: number, digits = 0) => `${(x * 100).toFixed(digits)}%`;
