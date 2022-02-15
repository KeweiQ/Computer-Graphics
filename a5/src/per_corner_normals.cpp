#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  
  std::vector<std::vector<int> > VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  for (int i = 0; i < F.rows(); i++) {
      const Eigen::RowVector3d a = V.row(F(i, 0));
      const Eigen::RowVector3d b = V.row(F(i, 1));
      const Eigen::RowVector3d c = V.row(F(i, 2));
      const Eigen::RowVector3d nf = triangle_area_normal(a, b, c).normalized();

      for (int j = 0; j < F.cols(); j++) {
        auto sum = Eigen::RowVector3d(0, 0, 0);
        const int num_faces = VF[F(i, j)].size();

        for (int k = 0; k < num_faces; k++) {
          const Eigen::RowVector3d aa = V.row(F(VF[F(i, j)][k], 0));
          const Eigen::RowVector3d bb = V.row(F(VF[F(i, j)][k], 1));
          const Eigen::RowVector3d cc = V.row(F(VF[F(i, j)][k], 2));
          const Eigen::RowVector3d normal = triangle_area_normal(aa, bb, cc);
          const Eigen::RowVector3d ng = normal.normalized();

          if (ng.dot(nf) > cos(corner_threshold * M_PI / 180.0)) {
            sum += normal;
          }
        }

        N.row(i * F.cols() + j) = sum.normalized();
      }
  }


  ////////////////////////////////////////////////////////////////////////////
}
