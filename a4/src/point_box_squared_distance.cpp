#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////

  // Source: https://stackoverflow.com/questions/5254838/calculating-distance-between-a-point-and-a-rectangular-box-nearest-point

  double dist_x = fmax(fmax(box.min_corner(0) - query(0), query(0) - box.max_corner(0)), 0);
  double dist_y = fmax(fmax(box.min_corner(1) - query(1), query(1) - box.max_corner(1)), 0);
  double dist_z = fmax(fmax(box.min_corner(2) - query(2), query(2) - box.max_corner(2)), 0);
  double squared_distance = pow(dist_x, 2) + pow(dist_y, 2) + pow(dist_z, 2);

  return squared_distance;
  ////////////////////////////////////////////////////////////////////////////
}
