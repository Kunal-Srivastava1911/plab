/* Spec section 7. */
export interface CostParams {
  C_ref: number;
  C_hit: number;
  n: number;
  C_ctx: number;
  C_p: number;
  P_br: number;
  g: number;
}

export const DEFAULT_COST: CostParams = { C_ref: 15, C_hit: 10, n: 4, C_ctx: 1, C_p: 6, P_br: 17, g: 0.1 };

export const BASELINE_PRESETS = [
  { key: "simd", label: "SIMD tokenizer", C_ref: 8 },
  { key: "re2c", label: "Direct-coded (re2c)", C_ref: 15 },
  { key: "flex", label: "Table-driven (flex)", C_ref: 30 },
] as const;

export const fallbackCost = (p: CostParams) => p.C_ctx + p.g * (p.C_p + p.P_br);

export function speedup(p: CostParams, a: number): number {
  const F = fallbackCost(p);
  return p.C_ref / ((a * p.C_hit) / p.n + (1 - a) * (p.C_ref + F));
}

export function breakEven(p: CostParams): number {
  const F = fallbackCost(p);
  return F / (p.C_ref + F - p.C_hit / p.n);
}
