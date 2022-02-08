#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  
  I = -1;
  sqrD = std::numeric_limits<double>::infinity();
  const int num_points = points.rows();
  Eigen::RowVector3d point;
  double sqrD_temp;

  for (int i=0; i<num_points; i++) {
    point = points.row(i);
    sqrD_temp = (point - query).squaredNorm();

    if (sqrD_temp < sqrD) {
      sqrD = sqrD_temp;
      I = i;
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}
