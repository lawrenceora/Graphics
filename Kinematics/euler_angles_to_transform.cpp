#include <cmath>

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  Eigen::Affine3d A;

  A = Eigen::AngleAxisd(xzx(2) * M_PI / 180, Eigen::Vector3d::UnitX()) *
      Eigen::AngleAxisd(xzx(1) * M_PI / 180, Eigen::Vector3d::UnitZ()) *
      Eigen::AngleAxisd(xzx(0) * M_PI / 180, Eigen::Vector3d::UnitX());

  return A;
}
