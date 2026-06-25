# random-color-contrasts Domain Context

## Purpose

A CLI tool that generates foreground/background color pairs meeting WCAG contrast requirements for accessibility.

## Implementation

- **JavaScript**: `generateRandomColorContrast/index.js` + `generateRandomColorContrast/colors.js`
- **Python**: `generate_colors.py` (148 HTML colors)
- **C**: `c-port/main.c` (compiled binary)

## Use Cases

- **dwm** (dynamic window manager) — window title bar colors
- **dunst** (desktop notifications) — notification colors

## Contrast Logic

Uses the `get-contrast` API to ensure WCAG 4.5:1 ratio compliance. Falls back to:
1. Primary random color
2. Secondary random color (loop until contrast passes)

## Color Naming

For each color, returns the nearest match from:
- Pantone
- NTC
- RoyGBiv

Names are cosmetic—only hex codes matter for current use cases.

## Blocklist

Unused colors can be blacklisted in `COLOR_BLOCKLIST` in `generateRandomColorContrast/colors.js`.

