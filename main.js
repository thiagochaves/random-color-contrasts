const generateRandomColorContrast = require('./generateRandomColorContrast');
console.log('Generating random color contrast...');
const { description, colors, colorOne, colorTwo } = generateRandomColorContrast();
console.log('Generated random color contrast!');
console.log('Description:', description);
console.log('Full text:', colors);
console.log('Color One:', colorOne);
console.log('Color Two:', colorTwo);
