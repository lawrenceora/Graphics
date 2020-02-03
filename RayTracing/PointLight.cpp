#include <cmath>

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  Eigen::Vector3d v = p - q;
  d = v.normalized();
  max_t = std::sqrt(v.dot(v));
}
