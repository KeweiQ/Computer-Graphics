#include "euler_angles_to_transform.h"

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  /////////////////////////////////////////////////////////////////////////////
  
  double theta1 = xzx[0] * M_PI/180.0; 
  double theta2 = xzx[1] * M_PI/180.0; 
  double theta3 = xzx[2] * M_PI/180.0;

  Eigen::AngleAxis<double> A = Eigen::AngleAxisd(theta1, Eigen::Vector3d::UnitX());
  Eigen::AngleAxis<double> B = Eigen::AngleAxisd(theta2, Eigen::Vector3d::UnitZ());
  Eigen::AngleAxis<double> C = Eigen::AngleAxisd(theta3, Eigen::Vector3d::UnitX());

  Eigen::Affine3d M = Eigen::Affine3d(C * B * A);
  return M;

  /////////////////////////////////////////////////////////////////////////////
}
