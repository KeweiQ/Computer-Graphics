#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d AB = A.transpose() - B.transpose();
  Eigen::Vector3d AC = A.transpose() - C.transpose();
  Eigen::Vector3d D = ray.direction;
  Eigen::Vector3d AE = A.transpose() - ray.origin;

  double a = AB[0];
  double b = AB[1];
  double c = AB[2];
  double d = AC[0];
  double e = AC[1];
  double f = AC[2];
  double g = D[0];
  double h = D[1];
  double i = D[2];
  double j = AE[0];
  double k = AE[1];
  double l = AE[2];

  double M = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);
  double T = - (f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c)) / M;
  double gamma = (i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c)) / M;
  double beta = (j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g)) / M;

  if (T < min_t || T > max_t) {
    return false;
  } else if (beta < 0 || beta > 1) {
    return false;
  } else if (gamma < 0 || gamma > (1 - beta)) {
    return false;
  } else {
    t = T;
    return true;
  }

  ////////////////////////////////////////////////////////////////////////////
}

