#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

Eigen::Affine3d create_affine(
  const Skeleton & skeleton,
  const int index)
{
  if (skeleton[index].parent_index == -1) {
    return Eigen::Affine3d::Identity();
  } else {
    Eigen::Affine3d parent_T = create_affine(skeleton, skeleton[index].parent_index);
    Eigen::Affine3d T = parent_T * skeleton[index].rest_T * euler_angles_to_transform(skeleton[index].xzx) * skeleton[index].rest_T.inverse();
    return T;
  }
}

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  T.resize(skeleton.size(), Eigen::Affine3d::Identity());
  for (int i = 0; i < skeleton.size(); i++) {
    T[i] = create_affine(skeleton, i);
  }

  /////////////////////////////////////////////////////////////////////////////
}
