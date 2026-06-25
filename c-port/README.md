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
- HTML color name lookup (~70 common colors)
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

| Implementation | Runtime |
|---|---|
| C (`c-port/random-color-contrasts`) | 0.001-0.002s |
| JS (`src/main.js`) | ~27ms |
| **Speedup** | **10-30x faster** |
