#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////

  if (ray.direction.dot(normal) != 0) {
    t = (point - ray.origin).dot(normal) / ray.direction.dot(normal);
  
    if (t >= min_t) {
      n = normal.normalized();
      return true;
    }
  }
  return false;

  ////////////////////////////////////////////////////////////////////////////
}
