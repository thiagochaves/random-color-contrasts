# random-color-contrasts

CLI tool that generates random, accessible color pairs.

## Usage

```bash
make
./random-color-contrasts
```

Or with a deterministic pair:

```bash
./random-color-contrasts --hex AABBCC DDEEFF
```

`--hex` mode emits machine-readable output (one key=value per line):
`ratio`, `rating`, `name1`, `name2`.

## Output Format

```
Generating random color contrast...
Generated random color contrast!
Description: [ColorOne] (#AABBCC) and [ColorTwo] (#DDEEFF)
Full text: [ColorOne] #AABBCC
[ColorTwo] #DDEEFF

(Contrast ratio: 7.3:1 | AAA)
Color One: #AABBCC
Color Two: #DDEEFF
```

## Build

```bash
make          # Builds random-color-contrasts
make test     # Runs unit tests + shell smoke
make coverage # Branch coverage via gcov
make clean    # Removes binary + coverage artifacts
```

## Features

- WCAG 4.5:1 contrast ratio compliance
- HTML color name lookup (139 colors, nearest-match)
- 10% RGB tolerance for matching
- Luminance fallback for white/gray/black
- Color family fallback (Red/Green/Blue)
- ~1ms per call

## Architecture

Single-file implementation with:
- Embedded color database
- No heap allocation
- Safe string handling

## Performance

Measured on Linux, gcc `-O2`, 100 sequential runs after warm-up: **~1ms per call**.

The original JavaScript implementation (`~80ms per call`) was removed
in favor of the C port; see ADR 0003.

## Customization

- **C color definitions**: `main.c` (lines 18-148)

## Deferred Improvements

Things reviewed and intentionally not done. Listed so future work doesn't re-investigate.

**Unreachable branch coverage (~95% taken, stuck).** Two branches in `get_pantone` cannot fire with the current 139-entry table:

- `lum > 0.85` near-White fallback — brute-forced all 16.7M RGB triples. The maximum luminance achievable for an input with no table match within 78 Manhattan distance is **0.802**. Hitting the 0.85 threshold would require removing near-white entries (White, Snow, GhostWhite, WhiteSmoke, FloralWhite, etc.) just to manufacture a gap. Not worth the test fragility.
- `max_v == 0` div-by-zero guard — only `(0,0,0)` triggers it, and `(0,0,0)` matches Black in the table. Pure defensive dead code; the ternary exists only to prevent UB if the table were ever changed to omit Black.

Both remain visible in `make coverage` output so future readers can see they're intentional.

**`#include "../main.c"` in test harness.** Fragile if `main.c` moves, gets a second TU, or includes a conflicting header. The proper fix is extracting declarations to a `main.h`. Not done because the project is single-TU and the hack has not caused problems in practice.

**`--hex` mode accepts non-hex chars silently.** `./random-color-contrasts --hex ZZZZZZ YYYYYY` passes the length check, then `hex_to_rgb` returns 0, then the report emits `ratio=NaN`, `rating=N/A`, `name1=Black`, `name2=Black`. A explicit `[0-9A-Fa-f]{6}` validator would give a clearer error. Not done because the C toolchain's `get-contrast` consumer doesn't pass invalid hex, and the failure mode is at least non-destructive.

**Dedupe rating logic between `print_contrast_report` and `print_machine_report`.** Two callers, three lines each (`if ratio >= 7.0 / < 4.5 / else`). Extracting a `rating_for(ratio)` helper saves ~6 lines at the cost of one more indirection. Skip until there's a third caller.

**CI integration.** No CI exists yet; adding a GitHub Actions workflow to run `make test` would be premature. Revisit when the project gets any other CI.

**Move `srand` after the `--hex` early return.** Cosmetic. `--hex` doesn't call `rand`, so the seed runs only when needed regardless of placement.