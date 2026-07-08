#!/bin/sh
# Smoke test: run the binary, verify output shape (regex on each line).
# Does not assert on the contrast rating — content is random by design.
set -e

cd "$(dirname "$0")/.."
out=$(./random-color-contrasts 2>&1)

echo "$out" | grep -qE "^Description: .+ \(#[0-9A-F]{6}\) and .+ \(#[0-9A-F]{6}\)$" \
    || { echo "FAIL: Description line missing or malformed"; echo "$out"; exit 1; }

echo "$out" | grep -qE "^Full text: .+ #" \
    || { echo "FAIL: Full text line missing"; echo "$out"; exit 1; }

echo "$out" | grep -qE "^\(Contrast ratio: [0-9.]+:1 \| (AA|AAA|N/A)\)$" \
    || { echo "FAIL: Contrast rating line missing or invalid"; echo "$out"; exit 1; }

echo "$out" | grep -qE "^Color One: #[0-9A-F]{6}$" \
    || { echo "FAIL: Color One line missing"; echo "$out"; exit 1; }

echo "$out" | grep -qE "^Color Two: #[0-9A-F]{6}$" \
    || { echo "FAIL: Color Two line missing"; echo "$out"; exit 1; }

echo "smoke ok"