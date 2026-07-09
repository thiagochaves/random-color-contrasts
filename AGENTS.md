# random-color-contrasts Agent Guide

## Quick Start

- Build: `cd c-port && make`
- Run: `./c-port/random-color-contrasts`
- Test: `cd c-port && make test`
- Clean: `cd c-port && make clean`

## Architecture

**Entry point**: `c-port/main.c` — single-file C implementation, compiled to `c-port/random-color-contrasts`.

**Core**: In-process WCAG contrast formula (`get_lum_hex`, `get_contrast_ratio`). The JavaScript implementation referenced `get-contrast` from npm; see ADR 0003 for why it was removed.

## Customization

- **C color definitions**: `c-port/main.c` (lines 18-148) — the `html_colors[]` table.

## Agent skills

### Issue tracker

Local markdown under `.scratch/`. See `docs/agents/issue-tracker.md`.

### Triage labels

Using canonical labels: `needs-triage`, `needs-info`, `ready-for-agent`, `ready-for-human`, `wontfix`. See `docs/agents/triage-labels.md`.

### Domain docs

Single-context layout with `CONTEXT.md` and `docs/adr/` at repo root. See `docs/agents/domain.md`.

---

**Setup by setup-matt-pocock-skills.**