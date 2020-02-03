#include <cmath>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  double c = v * s;
  double h_bar = h/60.0;
  double x = c * (1.0 - std::fabs( std::fmod(h_bar, 2.0) - 1.0));
  double m = v - c;

  if (h_bar <= 1.0){
    r = c + m;
    g = x + m;
    b = m;
  } else if (h_bar <= 2.0){
    r = x + m;
    g = c + m;
    b = m;
  } else if (h_bar <= 3.0){
    r = m;
    g = c + m;
    b = x + m;
  } else if (h_bar <= 4.0){
    r = m;
    g = x + m;
    b = c + m;
  } else if (h_bar <= 5.0){
    r = x + m;
    g = m;
    b = c + m;
  } else {
    r = c + m;
    g = m;
    b = x + m; 
  }
}
