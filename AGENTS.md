# random-color-contrasts Agent Guide

## Quick Start

- Build: `make`
- Run: `./random-color-contrasts`
- Test: `make test`
- Clean: `make clean`

## Architecture

**Entry point**: `main.c` — single-file C implementation.

**Core**: In-process WCAG contrast formula (`get_lum_hex`, `get_contrast_ratio`). The JavaScript implementation referenced `get-contrast` from npm; see ADR 0003 for why it was removed.

## Customization

- **C color definitions**: `main.c` (lines 18-148) — the `html_colors[]` table.

## Agent skills

### Issue tracker

Local markdown under `.scratch/`. See `docs/agents/issue-tracker.md`.

### Triage labels

Using canonical labels: `needs-triage`, `needs-info`, `ready-for-agent`, `ready-for-human`, `wontfix`. See `docs/agents/triage-labels.md`.

### Domain docs

Single-context layout with `CONTEXT.md` and `docs/adr/` at repo root. See `docs/agents/domain.md`.

---

**Setup by setup-matt-pocock-skills.**