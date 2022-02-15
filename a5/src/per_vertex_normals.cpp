#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.cpp"

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  ////////////////////////////////////////////////////////////////////////////

  std::vector<std::vector<int> > VF;
  vertex_triangle_adjacency(F, V.rows(), VF);
  
  for (int i = 0; i < V.rows(); i++) {
      auto sum = Eigen::RowVector3d(0, 0, 0);
      const int num_faces = VF[i].size();

      for (int j = 0; j < num_faces; j++) {
        Eigen::RowVector3i face = F.row(VF[i][j]);
        const Eigen::RowVector3d a = V.row(face[0]);
        const Eigen::RowVector3d b = V.row(face[1]);
        const Eigen::RowVector3d c = V.row(face[2]);
        sum += triangle_area_normal(a, b, c);
      }

      N.row(i) = sum.normalized();
  }

  ////////////////////////////////////////////////////////////////////////////
}
