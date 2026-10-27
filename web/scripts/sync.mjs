// Copy results/*.json into web/public/results/ (spec section 10).
import { copyFileSync, existsSync, mkdirSync } from "node:fs";
import { dirname, join } from "node:path";
import { fileURLToPath } from "node:url";

const here = dirname(fileURLToPath(import.meta.url));
const src = join(here, "..", "..", "results");
const dst = join(here, "..", "public", "results");
mkdirSync(dst, { recursive: true });
for (const f of ["limit_study.json", "bench.json", "difftest.json"]) {
  if (existsSync(join(src, f))) {
    copyFileSync(join(src, f), join(dst, f));
    console.log(`synced ${f}`);
  } else {
    console.warn(`missing results/${f}`);
  }
}
