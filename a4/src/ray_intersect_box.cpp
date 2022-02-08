#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox & box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  const double x_min = box.min_corner(0);
  const double x_max = box.max_corner(0);
  const double y_min = box.min_corner(1);
  const double y_max = box.max_corner(1);
  const double z_min = box.min_corner(2);
  const double z_max = box.max_corner(2);

  const double xd = ray.direction(0);
  const double xe = ray.origin(0);
  const double yd = ray.direction(1);
  const double ye = ray.origin(1);
  const double zd = ray.direction(2);
  const double ze = ray.origin(2);

  double tx_min;
  double tx_max;
  double ty_min;
  double ty_max;
  double tz_min;
  double tz_max;

  const double a = 1 / xd;
  if (a >= 0) {
    tx_min = a * (x_min - xe);
    tx_max = a * (x_max - xe);
  } else {
    tx_min = a * (x_max - xe);
    tx_max = a * (x_min - xe);
  }

  const double b = 1 / yd;
  if (b >= 0) {
    ty_min = b * (y_min - ye);
    ty_max = b * (y_max - ye);
  } else {
    ty_min = b * (y_max - ye);
    ty_max = b * (y_min - ye);
  }
  
  const double c = 1 / zd;
  if (c >= 0) {
    tz_min = c * (z_min - ze);
    tz_max = c * (z_max - ze);
  } else {
    tz_min = c * (z_max - ze);
    tz_max = c * (z_min - ze);
  }

  if (fmin(fmin(tx_max, ty_max), tz_max) < fmax(fmax(tx_min, ty_min), tz_min)) {
    return false;
  } else if (fmin(fmin(tx_max, ty_max), tz_max) < min_t || fmax(fmax(tx_min, ty_min), tz_min) > max_t) {
    return false;
  } else {
    return true;
  }

  ////////////////////////////////////////////////////////////////////////////
}
