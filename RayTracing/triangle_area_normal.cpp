#include <Eigen/Geometry>

Eigen::RowVector3d triangle_area_normal(
  const Eigen::RowVector3d & a, 
  const Eigen::RowVector3d & b, 
  const Eigen::RowVector3d & c)
{
  Eigen::Vector3d u = a.transpose() - b.transpose();
  Eigen::Vector3d v = a.transpose() - c.transpose();
  Eigen::RowVector3d cross = u.cross(v).transpose();

  // The length of the cross-product is the area of the parallelogram.
  return cross / 2;

}
