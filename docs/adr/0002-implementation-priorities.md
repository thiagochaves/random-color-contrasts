# ADR 0002: Implementation Strategy

## Context

The project exists in two languages: JavaScript and C.

## Decision

**Priorities**:

1. **C implementation** — fastest (~0.001s per call), for dwm/dunst
2. **JavaScript** — ~0.07s per call, easy to extend

Only maintain one implementation at a time:
- When C changes, update JS
- For new features, start with JS first

## Benchmark (100 iterations)

| Implementation | Total Time (100 calls) | Per Call |
|---|---|---|
| C (`c-port/random-color-contrasts`) | ~0.1s | ~0.001s |
| JS (`main.js`) | ~7.5s | ~0.07s |

**Speedup**: C is ~70x faster than JS for tight loops.

## Status

Accepted: `2026-06-25`

## Consequences

- Simpler codebase
- C performance preferred for performance-critical paths (dwm)
- JavaScript fine for occasional interactive use
