#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  /////////////////////////////////////////////////////////////////////////////
  
  U.resize(V.rows(), 3);

  for (int i = 0; i < V.rows(); i++) {
    Eigen::Vector3d vertex = V.row(i).transpose();

    for (int j = 0; j < skeleton.size(); j++) {
      if (W(i, skeleton[j].weight_index) > -1) {
        vertex += T[j] * vertex * W(i, skeleton[j].weight_index);
      }
    }

    U(i, 0) = vertex(0);
    U(i, 1) = vertex(1);
    U(i, 2) = vertex(2);
  }

  /////////////////////////////////////////////////////////////////////////////
}
