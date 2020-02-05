#include <cmath>

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  Eigen::RowVector3d mid = 0.5*(box.max_corner + box.min_corner);
  double width = std::fabs(box.max_corner(0) - box.min_corner(0));
  double height = std::fabs(box.max_corner(1) - box.min_corner(1));
  double depth = std::fabs(box.max_corner(2) - box.min_corner(2));

  // Calculate minimum distance in each axis of direction
  double dx = std::max( std::fabs(query(0) - mid(0)) - width/2, 0.0);
  double dy = std::max( std::fabs(query(1) - mid(1)) - height/2, 0.0);
  double dz = std::max( std::fabs(query(2) - mid(2)) - depth/2, 0.0);

  double ans = dx*dx + dy*dy + dz*dz;

  return ans;
  
}
