void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  for (int i = 0; i < height*width; i++){
    unsigned char r = rgb[3*i];
    unsigned char g = rgb[3*i+1];
    unsigned char b = rgb[3*i+2];

    gray[i] = 0.2126*r + 0.7152*g + 0.0722*b;
  }
}



