#include <cmath>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  // Check if ray is inside the box:
  if (box.min_corner(0) <= ray.origin(0) && ray.origin(0) <= box.max_corner(0)){
    if (box.min_corner(1) <= ray.origin(1) && ray.origin(1) <= box.max_corner(1)){
      if (box.min_corner(2) <= ray.origin(2) && ray.origin(2) <= box.max_corner(2)){
        return true;
      }
    }
  }
  
  double tmin[3];
  double tmax[3];
  double a;

  // Calculate txmin and txmax:
  for (int i = 0; i < 3; i++){
    a = 1/ray.direction(i);
    if (a >= 0){
      tmin[i] = a*(box.min_corner(i) - ray.origin(i));
      tmax[i] = a*(box.max_corner(i) - ray.origin(i));
    } else {
      tmin[i] = a*(box.max_corner(i) - ray.origin(i));
      tmax[i] = a*(box.min_corner(i) - ray.origin(i));
    }
  }

  // Check for overlaps. Return false if not:
  if (tmin[0] > tmax[1] || tmin[1] > tmax[0]){
    return false;
  } else if (tmin[1] > tmax[2] || tmin[2] > tmax[1]){
    return false;
  } else if (tmin[2] > tmax[0] || tmin[0] > tmax[2]){
    return false;
  } 

  // Check if overlap is within range. Return false if not
  int min_o = std::max(tmin[0], std::max(tmin[1], tmin[2]));
  int max_o = std::min(tmax[0], std::min(tmax[1], tmax[2]));
  if (max_o < min_t || max_t < min_o){
    return false;
  }

  return true;
  
}
