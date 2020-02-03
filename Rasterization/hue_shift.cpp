#include <cmath>

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  double h;
  double s;
  double v;

  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
        int curr = 3*(width*i + j);
        double r = static_cast<double>(rgb[curr]) / 255.0;
        double g = static_cast<double>(rgb[curr + 1]) / 255.0;
        double b = static_cast<double>(rgb[curr + 2]) / 255.0;

        rgb_to_hsv(r, g, b, h, s, v);
        h = h + shift;
        if (h > 360.0){
          h = h - 360.0;
        }
        hsv_to_rgb(h, s, v, r, g, b);

        shifted[curr] = static_cast<unsigned char>(r * 255.0);
        shifted[curr + 1] = static_cast<unsigned char>(g * 255.0);
        shifted[curr + 2] = static_cast<unsigned char>(b * 255.0);
    }
  }
}
