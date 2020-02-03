void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      // Blue
      if ((i % 2 == 0) && (j % 2 == 1)){
        bayer[width*i + j] = rgb[3*(width*i + j) + 2];

      // Red
      } else if ((i % 2 == 1) && (j % 2 == 0)){
        bayer[width*i + j] = rgb[3*(width*i + j)];

      // Green
      } else {
        bayer[width*i + j] = rgb[3*(width*i + j) + 1];
      }
    }
  }
}
