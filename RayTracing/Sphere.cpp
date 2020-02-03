#include <cmath>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  Eigen::Vector3d ec = ray.origin - center;
  double a = ray.direction.dot(ray.direction);
  double b = ray.direction.dot(ec);
  double c = ec.dot(ec) - std::pow(radius, 2);
  double discriminant = std::pow(b, 2) - a*c;
  
  if (discriminant < 0){
    return false;
  } 

  double t_1 = (-b - std::sqrt(discriminant)) / a;
  double t_2 = (-b + std::sqrt(discriminant)) / a;

  double t_min = std::min(t_1, t_2);
  double t_max = std::max(t_1, t_2);

  if (t_min >= min_t){
    t = t_min;
  } else if (t_max >= min_t){
    t = t_max;
  } else {
    return false;
  }

  Eigen::Vector3d p = ray.origin + t*ray.direction;
  n = (p - center)/radius;
  return true;
}

