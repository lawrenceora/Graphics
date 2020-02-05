#include <Eigen/Dense>
#include <cmath>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  // Store size of keyframes
  int s = keyframes.size();

  // Return zero vector if inputs are invalid:
  if (s == 0 || t < keyframes[0].first || keyframes[s-1].first < t){
    return Eigen::Vector3d::Zero();
  }

  // Get the necessary values.
  std::pair<double, Eigen::Vector3d> f0, f1, f2, f3;

  for (int i = 0; i < s-1; i++){
    if (keyframes[i].first <= t && t <= keyframes[i+1].first){
      f0 = keyframes[std::max(i-1, 0)];
      f1 = keyframes[i];
      f2 = keyframes[i+1];
      f3 = keyframes[std::min(i+2, s-1)];
      break;
    } 
  }

  // Centralize t to be between 0 and 1. Calculate its powers, and gradients
  double t1 = (t - f1.first) / (f2.first - f1.first);
  double t2 = t1*t1;
  double t3 = t2*t1;
  Eigen::Vector3d m1 = (f2.second - f0.second) / (f2.first - f0.first);
  Eigen::Vector3d m2 = (f3.second - f1.second) / (f3.first - f1.first);

  // Return unit interval interpolation.
  return (2*t3 - 3*t2 +  1) * f1.second
       + (  t3 - 2*t2 + t1) * m1
       - (2*t3 - 3*t2)      * f2.second
       + (  t3 -   t2)      * m2;
}
