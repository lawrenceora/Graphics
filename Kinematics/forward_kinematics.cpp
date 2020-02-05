#include <functional> // std::function

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  T.resize(skeleton.size(), Eigen::Affine3d::Identity());
  Eigen::Vector3d angle;

  // Instead of a recursive call, just build the array from the bottom-up
  for (int i = 0; i < skeleton.size(); i++){
    Bone bone = skeleton[i];
    // Ignore root bone since T is already initialized to Identity()
    if (bone.parent_index != -1){
	// We cap values of angle animation.
        angle = bone.xzx.cwiseMax(bone.xzx_min);
        angle = angle.cwiseMin(bone.xzx_max);
        T[i] = T[bone.parent_index] * bone.rest_T * euler_angles_to_transform(angle) * bone.rest_T.inverse();
    }
  }
}
