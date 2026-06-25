# random-color-contrasts Agent Guide

## Quick Start

- Run: `npm start` or `node main.js`
- Build C version: `cd c-port && make`
- Clean build: `cd c-port && make clean`

## Architecture

**Entry point**: `main.js` calls `generateRandomColorContrast()` from `generateRandomColorContrast/index.js`.

**Core**: Uses `get-contrast` API for WCAG-compliant color ratios.

**Multi-language**: Same logic exists in:
- C: `c-port/main.c` (compiled to `c-port/random-color-contrasts`) — 10-30x faster than JS
- JavaScript: `generateRandomColorContrast/`

## Customization

- Blocklist colors: Edit `COLOR_BLOCKLIST` in `generateRandomColorContrast/colors.js`
- C color definitions: `c-port/main.c` (lines 18-148)
- JS color logic: `generateRandomColorContrast/colors.js`

## Agent skills

### Issue tracker

Local markdown under `.scratch/`. See `docs/agents/issue-tracker.md`.

### Triage labels

Using canonical labels: `needs-triage`, `needs-info`, `ready-for-agent`, `ready-for-human`, `wontfix`. See `docs/agents/triage-labels.md`.

### Domain docs

Single-context layout with `CONTEXT.md` and `docs/adr/` at repo root. See `docs/agents/domain.md`.

---

**Setup by setup-matt-pocock-skills.**
