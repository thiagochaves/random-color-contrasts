# ADR 0001: Color Database Strategy

## Context

The tool needs to generate foreground/background color pairs with good contrast.

## Decision

Use standard HTML color names with a fallback mechanism:

1. Generate random RGB colors
2. Check WCAG contrast ratio
3. For each color, find nearest name from Pantone/NTC/RoyGBiv
4. Allow blacklisting of unwanted colors

## Status

Accepted: `2026-06-25`

## Consequences

- Consistent color naming across implementations
- Some colors may not have perfect name matches
- Blacklist can be used for future adjustments
