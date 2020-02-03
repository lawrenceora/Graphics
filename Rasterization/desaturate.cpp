void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  double h;
  double s;
  double v;

  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      int curr = 3*(width*i + j);
      double r = static_cast<double>(rgb[curr]) / 255;
      double g = static_cast<double>(rgb[curr + 1]) / 255;
      double b = static_cast<double>(rgb[curr + 2]) / 255;

      rgb_to_hsv(r, g, b, h, s, v);
      s = s * (1-factor);
      if (s < 0.0){
        s = 0.0;
      }
      hsv_to_rgb(h, s, v, r, g, b);

      desaturated[curr] = static_cast<unsigned char>(r * 255);
      desaturated[curr + 1] = static_cast<unsigned char>(g * 255);
      desaturated[curr + 2] = static_cast<unsigned char>(b * 255);
    }
  }
}
