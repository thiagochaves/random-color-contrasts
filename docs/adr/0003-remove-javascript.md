# ADR 0003: Remove the JavaScript Implementation

## Context

The project existed in two languages — JavaScript (root: `main.js`,
`generateRandomColorContrast/`) and C (`c-port/`). Per ADR 0002 the
intent was to maintain both, prioritizing C for performance-critical
use (dwm/dunst) and using JS for prototyping.

In practice the JS port was never extended after the C port reached
feature parity, and the parity test (comparing C's contrast ratio
against JS `get-contrast`) was the only consumer of the JS code
after the C unit tests were added. The cost of maintaining two
implementations of the WCAG contrast formula and the color-naming
heuristic exceeded the benefit.

## Decision

Drop the JavaScript implementation. The C implementation is the only
one kept. The parity test is removed along with it (no second source
of truth to be paritious with).

The C source is `main.c`. The directory layout at the time of this
ADR is `c-port/main.c`; a follow-up refactor moves it to the repo
root.

## Tradeoffs

**Lost:** The `COLOR_BLOCKLIST` mechanism (env-var-driven filter on
color names returned by `color-namer`). This feature has been empty
since commit `235f454` ("Remove mastodon and blocklist",
2024-07-10) — its filter machinery is dead code. No user-supplied
config is lost.

**Kept:** The C-only feature set (HTML color name lookup, WCAG
contrast, `--hex` mode, machine-readable output for tests).

## Status

Accepted: `2026-07-08`

## Consequences

- Simpler codebase: one implementation, one set of dependencies.
- C remains the only impl; ADR 0002's dual-language strategy is
  superseded by this ADR.
- New features land in C directly; no JS→C porting step.