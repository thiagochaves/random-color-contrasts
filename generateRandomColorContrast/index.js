const { getColors } = require("./colors");

function generateRandomColorContrast() {
  const colors = getColors();
  const { colorOne, colorTwo, ratio, score } = colors;

  const text = [
    `${colorOne.name} ${colorOne.hex}`,
    `${colorTwo.name} ${colorTwo.hex}`,
    ``,
    `(Contrast ratio: ${ratio.toFixed(1)}:1 | ${score})`,
  ].join("\n");
  const imageDescription = `${colorOne.name} (${colorOne.hex}) and ${colorTwo.name} (${colorTwo.hex})`;

  return {
    description: imageDescription,
    colors: text,
    colorOne: colorOne.hex,
    colorTwo: colorTwo.hex,
  };
}

module.exports = generateRandomColorContrast;
