#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
  
  Eigen::VectorXd positions = Eigen::VectorXd::Zero(3*b.size());
  std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d> > T;
  forward_kinematics(skeleton, T);

  for (int i = 0; i < b.rows(); i++) {
    Eigen::Vector4d homo_position = T[b[i]] * skeleton[b[i]].rest_T * Eigen::Vector4d(skeleton[b[i]].length, 0.0, 0.0, 1.0);
    positions[i * 3] = homo_position[0] / homo_position[3];
    positions[i * 3 + 1] = homo_position[1] / homo_position[3];
    positions[i * 3 + 2] = homo_position[2] / homo_position[3];
  }

  return positions;

  /////////////////////////////////////////////////////////////////////////////
}
