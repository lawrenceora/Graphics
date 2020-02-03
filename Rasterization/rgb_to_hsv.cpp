#include <algorithm>
#include <cmath>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  double max = std::max(r, std::max(g, b));
  double min = std::min(r, std::min(g, b));

  if (max == min){
    h = 0.0;
  } else if (max == r){
    h = 60.0 * (g-b) / (max - min);
  } else if (max == g){
    h = 60.0 * (2.0 + ((b-r)/(max-min)));
  } else {
    h = 60.0 * (4.0 + ((r-g)/(max-min)));
  }

  if (h > 360.0){
    h = h - 360.0;
  } else if (h < 0.0){
    h = h + 360.0;
  }

  if (max == 0.0){
    s = 0.0;
  } else {
    s = (max-min)/max;
  }

  v = max;
}
