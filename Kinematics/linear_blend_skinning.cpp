void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  U = Eigen::MatrixXd::Zero(V.rows(), 3);
  int weight_ij;
  Eigen::Vector3d vi;

  for (int i = 0; i < V.rows(); i++){
    for (int j = 0; j < skeleton.size(); j++){
      weight_ij = skeleton[j].weight_index;
      if (weight_ij != -1){
        vi = V.row(i);
        U.row(i) += W(i, weight_ij) * (T[j] * vi);
      }
    }
  }
}
