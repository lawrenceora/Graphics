void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      reflected[3*(width*i + j)] = input[3*(width*(i+1) - 1 - j)];
      reflected[3*(width*i + j) + 1] = input[3*(width*(i+1) - 1 - j) + 1];
      reflected[3*(width*i + j) + 2] = input[3*(width*(i+1) - 1 - j) + 2];
    }
  }
}
