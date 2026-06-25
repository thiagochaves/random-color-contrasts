# random-color-contrasts Agent Guide

## Quick Start

- Run: `npm start` or `node main.js`
- Build C version: `cd c-port && make`
- Clean build: `cd c-port && make clean`

## Architecture

**Entry point**: `main.js` calls `generateRandomColorContrast()` from `generateRandomColorContrast/index.js`.

**Core**: Uses `get-contrast` API for WCAG-compliant color ratios.

**Multi-language**: Same logic exists in:
- Python: `generate_colors.py` (148 HTML colors)
- C: `c-port/main.c` (compiled to `c-port/random-color-contrasts`)

## Customization

- Blocklist colors: Edit `COLOR_BLOCKLIST` in `generateRandomColorContrast/colors.js`
- Color definitions: `generate_colors.py` (lines 4-115), `c-port/main.c` (lines 18-148)
