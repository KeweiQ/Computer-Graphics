#include "per_face_normals.h"
#include "triangle_area_normal.h"

void per_face_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  ////////////////////////////////////////////////////////////////////////////
  
  N.resize(F.rows(), 3);

  for (int i = 0; i < F.rows(); i++) {
    const Eigen::RowVector3d a = V.row(F(i, 0));
    const Eigen::RowVector3d b = V.row(F(i, 1));
    const Eigen::RowVector3d c = V.row(F(i, 2));
    N.row(i) = triangle_area_normal(a, b, c).normalized();
  }

  ////////////////////////////////////////////////////////////////////////////
}
