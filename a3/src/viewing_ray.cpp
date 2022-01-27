#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  
  double element_width = camera.width / width;
  double element_height = camera.height / height;
  double center_idx_j = j - width / 2;
  double center_idx_i = - i + height / 2;
  double u_value = element_width * center_idx_j + element_width / 2;
  double v_value = element_height * center_idx_i - element_height / 2;

  Eigen::Vector3d screen_dir = camera.u * u_value + camera.v * v_value;
  Eigen::Vector3d eye_dir = - camera.w * camera.d;
  Eigen::Vector3d ray_dir = screen_dir + eye_dir;

  ray.origin = camera.e;
  ray.direction = ray_dir;
  
  ////////////////////////////////////////////////////////////////////////////
}
