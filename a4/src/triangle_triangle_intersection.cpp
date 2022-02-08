#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  
  Ray ray1 = Ray(A0, A1 - A0);
  Ray ray2 = Ray(A1, A2 - A1);
  Ray ray3 = Ray(A2, A0 - A2);

  double t;
  bool result = ray_intersect_triangle(ray1, B0, B1, B2, 0, 1, t) || ray_intersect_triangle(ray2, B0, B1, B2, 0, 1, t) || ray_intersect_triangle(ray3, B0, B1, B2, 0, 1, t);

  return result; 

  ////////////////////////////////////////////////////////////////////////////
}
