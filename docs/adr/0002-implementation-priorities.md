# ADR 0002: Implementation Strategy

## Context

The project exists in three languages: JavaScript, Python, and C.

## Decision

**Priorities**:
1. **C implementation** — fastest (0.001-0.002s), for dwm/dunst
2. **JavaScript** — ~27ms, easy to extend
3. **Python** — for validation/testing

Only maintain one implementation at a time:
- When C changes, update JS/Python
- For new features, start with JS first

## Status

Accepted: `2026-06-25`

## Consequences

- Simpler codebase
- C performance preferred for performance-critical paths
- JS/Python can stay simpler
