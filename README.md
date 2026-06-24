# random-color-contrasts

CLI tool that generates random, accessible color pairs.

## Usage

```bash
npm start
```

Or run `main.js` directly.

## Output Format

```
Generating random color contrast...
Generated random color contrast!
Description: [Description]
Full text: [HexColorOne] and [PantoneName], [HexColorTwo] and [PantoneName]
Color One: [HEXCOLOR] - [ColorName]
Color Two: [HEXCOLOR] - [ColorName]
```

## Options

- **Blocklist colors**: Edit `COLOR_BLOCKLIST` in `colors.js`
- **API accessibility**: Uses `get-contrast` to ensure WCAG compliant ratios
- **Color naming**: Returns Pantone, NTC, and RoyGBiv names (nearest match)

## Dependencies
