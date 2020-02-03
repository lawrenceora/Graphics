bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  double denom = ray.direction.dot(normal);
  double intersection = (point - ray.origin).dot(normal) / denom;

  if (intersection >= min_t){
    t = intersection;
    n = normal.normalized();
    return true;
  }
  return false;
}

