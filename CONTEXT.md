# random-color-contrasts Domain Context

## Purpose

A CLI tool that generates foreground/background color pairs meeting WCAG contrast requirements for accessibility.

## Implementation

- **C**: `c-port/main.c` (compiled binary) — single source of truth.

JavaScript removed; see ADR 0003.

## Use Cases

- **dwm** (dynamic window manager) — window title bar colors
- **dunst** (desktop notifications) — notification colors

## Contrast Logic

In-process WCAG formula: sRGB→linear decode, then weighted sum
(0.2126, 0.7152, 0.0722), then `(Lmax + 0.05) / (Lmin + 0.05)`. Loop
re-rolls color pairs until contrast passes 4.5.

## Color Naming

For each color, returns the nearest match from a 139-entry HTML
named-color table (kept in sync with the MDN CSS spec). 10% RGB
tolerance per channel. Falls back to a luminance-based "Black"/
"White" classification, then to a "Red/Green/Blue family" guess.

Names are cosmetic — only hex codes matter for current use cases.