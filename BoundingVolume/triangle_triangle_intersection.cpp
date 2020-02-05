bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  Ray ray(Eigen::Vector3d(0,0,0), Eigen::Vector3d(0,0,0));
  double edge_length, temp_t;
  Eigen::RowVector3d A[3] = {A0, A1, A2};
  Eigen::RowVector3d B[3] = {B0, B1, B2};

  // Use the edges of A to check for intersection of B
  for (int i = 0; i < 3; i++){
    ray.origin = A[i].transpose();
    ray.direction = (A[(i+1) % 3] - A[i]).transpose();
    edge_length = ray.direction.norm();
    if (ray_intersect_triangle(ray, B0, B1, B2, 0, edge_length, temp_t)){
      return true;
    }
  }

  // Use the edge of B to check for intersection of A
  for (int j = 0; j < 3; j++){
    ray.origin = B[j].transpose();
    ray.direction = (B[(j+1) % 3] - B[j]).transpose();
    edge_length = ray.direction.norm();
    if (ray_intersect_triangle(ray, A0, A1, A2, 0, edge_length, temp_t)){
      return true;
    }
  }

  return false;
}
