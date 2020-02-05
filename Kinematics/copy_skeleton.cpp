Skeleton copy_skeleton(
  const Skeleton & skeleton, 
  const Eigen::VectorXd & A)
{

  // Copy all transformations from previous skeleton (rest_T).
  Skeleton copy = skeleton;
  Eigen::Vector3d angle;  

  // Update its angle.
  for (int i = 0; i < A.size()/3; i++){
    angle = A.segment(3*i, 3);
    copy[i].xzx = angle;
  }

  return copy;
}
