Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  Eigen::VectorXd tips = Eigen::VectorXd::Zero(3*b.size());
  Eigen::Vector3d canonical_T;

  // Perform the animation, store the transformations in T.
  std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d>> T;
  forward_kinematics(skeleton, T);

  // Move the tips from canonical to rest, then to pose.
  for (int i = 0; i < b.size(); i++){
    Bone bone = skeleton[b(i)];
    canonical_T << bone.length, 0, 0;
    tips.segment(3*i, 3) = T[b(i)] * bone.rest_T * canonical_T;
  }

  return tips;
}
