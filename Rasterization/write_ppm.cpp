#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  
  // Open file.
  std::ofstream file(filename);

  // Check if file succeeded.
  if (file.fail()){
    return false;
  }

  // PPM Header
  file << "P3\n" << width << ' ' << height << '\n' << "255\n";

  // If RGB image:
  if (num_channels == 3){
    for (int i = 0; i < height; i++){
      for (int j = 0; j < width; j++){
        int r = static_cast<int>(data[3*(i*width + j)]);
        int g = static_cast<int>(data[3*(i*width + j) + 1]);
        int b = static_cast<int>(data[3*(i*width + j) + 2]);
        file << r << ' ' << g << ' ' << b << '\t';
      }
      file << '\n';
    }

  // If Grayscale image:
  } else {
    for (int i = 0; i < height; i++){
      for (int j = 0; j < width; j++){
        int b = static_cast<int>(data[(i*width + j)]);
        file << b << ' ' << b << ' ' << b << '\t';
      }
      file << '\n';
    }
  }

  // Close file.
  file.close();

  return true;
}
