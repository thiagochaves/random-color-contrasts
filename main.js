const generateRandomColorContrast = require('./generateRandomColorContrast');
console.log('Generating random color contrast...');
const imageFilePath = `/dev/shm/colors.png`;
generateRandomColorContrast({ imageFilePath }).then(({
  path,
  description,
  colors,
  colorOne,
  colorTwo
}) => {
  console.log('Generated random color contrast!');
  console.log('Path:', path);
  console.log('Description:', description);
  console.log('Full text:', colors);
  console.log('Color One:', colorOne);
  console.log('Color Two:', colorTwo);
})
