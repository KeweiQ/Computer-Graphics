#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  /////////////////////////////////////////////////////////////////////////////
  
  J.resize(b.size() * 3, skeleton.size() * 3);
  Eigen::VectorXd transformed = transformed_tips(skeleton, b);
  Skeleton copy = skeleton;
  double da = 1.0e-7;

  for (int i = 0; i < skeleton.size(); i++){
    for (int j = 0; j < 3; j++){
      copy[i].xzx[j] += da;
      Eigen::VectorXd dx = transformed_tips(copy, b) - transformed;

      for (int k = 0; k < b.size() * 3; k++){
        J(k, i * 3 + j) = dx[k] / da;
      }
    }
  }

  /////////////////////////////////////////////////////////////////////////////
}
