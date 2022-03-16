#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  
  f = [&](const Eigen::VectorXd & A)->double
  {
    Skeleton skeleton_copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd skeleton_transformed = transformed_tips(skeleton_copy, b);

    double least_squares = 0.0;
    for (int i = 0; i < b.size(); i++) {
      Eigen::Vector3d xba = Eigen::Vector3d(skeleton_transformed[i * 3], skeleton_transformed[i * 3 + 1], skeleton_transformed[i * 3 + 2]);
      Eigen::Vector3d q = Eigen::Vector3d(xb0[i * 3], xb0[i * 3 + 1], xb0[i * 3 + 2]);
      least_squares += (xba - q).squaredNorm();
    }

    return least_squares;
  };

  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {
    Eigen::MatrixXd J;
    Skeleton skeleton_copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd skeleton_transformed = transformed_tips(skeleton_copy, b);
    kinematics_jacobian(skeleton_copy, b, J);
    
    Eigen::VectorXd dEx_dx = Eigen::VectorXd::Zero(b.size() * 3);
    for (int i = 0; i < dEx_dx.size(); i++) {
      dEx_dx[i] = 2 * (skeleton_transformed[i] - xb0[i]);
    }

    return J.transpose() * dEx_dx;
  };

  proj_z = [&](Eigen::VectorXd & A)
  {
    assert(skeleton.size() * 3 == A.size());
    for (int i = 0; i < skeleton.size(); i++) {
      for (int j = 0; j < 3; j++) {
        A[i * 3 + j] = std::max(skeleton[i].xzx_min[j], std::min(skeleton[i].xzx_max[j], A[i * 3 + j]));
      }
    }
  };

  /////////////////////////////////////////////////////////////////////////////
}
