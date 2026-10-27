export interface Meta {
  commit: string;
  date: string;
  machine: string;
  cpu: string;
  compiler: string;
  flags: string;
  runs: number;
}

export interface CostAssumptions {
  C_hit: number;
  n: number;
  C_ctx: number;
  C_p: number;
  P_br: number;
}

export interface LimitRun {
  lang: string;
  predictor: string;
  budget_kb: number;
  order: number;
  W: number;
  acceptance?: string;
  files: number;
  tokens: number;
  bytes: number;
  coverage_tokens: number;
  coverage_bytes: number;
  mean_tokens_per_phrase: number;
  failed_probe_rate: number;
  partial_accept_rate: number;
  by_source: Record<string, number>;
  phrase_len_hist: number[];
  exactness_violations?: number;
}

export interface LimitStudy {
  meta: Meta;
  cost_model_assumptions: CostAssumptions;
  runs: LimitRun[];
}

export interface Stat {
  median: number;
  ci95: [number, number];
}

export interface BenchRow {
  lang: string;
  corpus: string;
  project: string;
  lexer: string;
  plab: boolean;
  config: string;
  mb_s: Stat;
  mtok_s: Stat;
  cycles_per_byte: number;
  instr_per_byte: number | null;
  branch_miss_per_tok: number | null;
  l1d_miss_per_kb: number | null;
  coverage_tokens: number;
  speedup?: number | null;
  runs?: number;
}

export interface Bench {
  meta: Meta;
  rows: BenchRow[];
}

export interface Difftest {
  meta: Meta;
  files: number;
  divergences: number;
  tokens?: number;
  configs?: { name: string; divergences: number; coverage_tokens: number }[];
}

export interface TraceIndexEntry {
  name: string;
  path: string;
  bytes: number;
  tokens: number;
  coverage: number;
}

export type Outcome = "commit" | "partial" | "miss" | "fallback";

export interface TraceToken {
  s: number;
  e: number;
  k: string;
  o: Outcome;
  ph: number | null;
  src: string | null;
  conf: number | null;
}

export interface TracePhrase {
  id: number;
  s: number;
  e: number;
  ntok: number;
  accepted: number;
  src: string;
  conf: number;
  mismatch_at: number | null;
  expected: number | null;
  actual: number | null;
}

export interface Trace {
  meta: Meta;
  name: string;
  path?: string;
  source: string;
  tokens: TraceToken[];
  phrases: TracePhrase[];
}
