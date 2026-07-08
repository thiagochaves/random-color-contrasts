#!/usr/bin/env node
/* Parity check: C binary's contrast ratio must match JS get-contrast within 0.01.
 * Run via `make test` from c-port/. Will be removed when JS port is dropped.
 */

const { execFileSync } = require("child_process");
const path = require("path");
const contrast = require("get-contrast");

const binary = path.join(__dirname, "..", "random-color-contrasts");

const PAIRS = [
    ["000000", "FFFFFF"],
    ["FFFFFF", "000000"],
    ["000000", "FF0000"],
    ["FF0000", "00FF00"],
    ["00FF00", "0000FF"],
    ["808080", "808080"],
    ["777777", "FFFFFF"],
    ["123456", "ABCDEF"],
    ["FF8040", "1A2B3C"],
    ["DEADBF", "0F0F0F"],
];

let failures = 0;

for (const [a, b] of PAIRS) {
    const out = execFileSync(binary, ["--hex", a, b], { encoding: "utf8" });
    const match = out.match(/^ratio=([\d.]+)$/m);
    if (!match) {
        console.error(`FAIL ${a} ${b}: could not parse C output\n${out}`);
        failures++;
        continue;
    }
    const cRatio = parseFloat(match[1]);
    const jsRatio = contrast.ratio("#" + a, "#" + b);
    const drift = Math.abs(cRatio - jsRatio);
    if (drift > 0.01) {
        console.error(`FAIL ${a} vs ${b}: C=${cRatio.toFixed(4)} JS=${jsRatio.toFixed(4)} drift=${drift.toFixed(4)}`);
        failures++;
    } else {
        console.log(`ok   ${a} vs ${b}: ${cRatio.toFixed(2)} (drift ${drift.toFixed(4)})`);
    }
}

console.log(`\n${PAIRS.length - failures}/${PAIRS.length} parity checks passed`);
process.exit(failures === 0 ? 0 : 1);