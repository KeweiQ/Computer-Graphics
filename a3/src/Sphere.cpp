#include "Sphere.h"
#include "Ray.h"
#include <math.h>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////

  double a = ray.direction.dot(ray.direction);
  double b = 2 * ray.direction.dot(ray.origin - center);
  double c = (ray.origin - center).dot(ray.origin - center) - std::pow(radius, 2);
  double discriminant = std::pow(b, 2) - 4 * a * c;

  if (discriminant < 0) {
    return false;
  
  } else {
    double r1 = ( - b + std::sqrt(discriminant)) / (2 * a);
    double r2 = ( - b - std::sqrt(discriminant)) / (2 * a);
  
    if (r1 < min_t) {
      return false;
    } else if (r1 >= min_t && r2 < min_t) {
      t = r1;
    } else {
      t = r2;
    }

    Eigen::Vector3d p = ray.origin + t * ray.direction;
    n = (p - center) / radius;
    return true;
  }

  ////////////////////////////////////////////////////////////////////////////
}

