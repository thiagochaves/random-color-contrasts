# C Implementation

## Build

```bash
make          # Builds random-color-contrasts binary
make clean    # Removes binary
```

## Usage

```bash
./random-color-contrasts
```

## Features

- WCAG 4.5:1 contrast ratio compliance
- HTML color name lookup (139 colors, nearest-match)
- 10% RGB tolerance for matching
- Luminance fallback for white/gray/black
- Color family fallback (Red/Green/Blue)
- 0.001-0.002s runtime

## Architecture

Single-file implementation with:
- Embedded color database
- No heap allocation
- Safe string handling

## Performance Comparison

| Implementation | Runtime (100 iterations) | Per Call |
|---|---|---|
| C (`c-port/random-color-contrasts`) | ~0.1s | ~0.001s |
| JS (`main.js`) | ~7.5s | ~0.07s |
| **Speedup** | | **~70x faster** |
