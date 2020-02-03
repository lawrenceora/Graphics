void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      rotated[3*(height*i + j)] = input[3*(width*(j+1) - (i+1))];
      rotated[3*(height*i + j) + 1] = input[3*(width*(j+1) - (i+1)) + 1];
      rotated[3*(height*i + j) + 2] = input[3*(width*(j+1) - (i+1)) + 2];
    }
  }

}
