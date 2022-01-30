#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <algorithm>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////

  Eigen::Vector3d rgb(0, 0, 0);
  rgb += objects[hit_id]->material->ka * 0.1; // ambient

  for (int i=0; i<lights.size(); i++) {
    Eigen::Vector3d d;
    double max_t;
    
    Ray light_ray;
    light_ray.origin = ray.origin + t * ray.direction;
    lights[i]->direction(light_ray.origin, light_ray.direction, max_t);

    int light_hit_id;
    double light_t;
    Eigen::Vector3d light_n;
    if (!first_hit(light_ray, 1.0e-5, objects, light_hit_id, light_t, light_n) || light_t >= max_t) {
      double nl_max = std::max(0.0, n.dot(light_ray.direction));
      double nh_max = std::max(0.0, n.dot((light_ray.direction - ray.direction.normalized()).normalized()));
      rgb += (objects[hit_id]->material->kd.array() * lights[i]->I.array()).matrix() * nl_max; // diffuse
      rgb += (objects[hit_id]->material->ks.array() * lights[i]->I.array()).matrix() * std::pow(nh_max, objects[hit_id]->material->phong_exponent); // specular
    }
  }

  return rgb;

  ////////////////////////////////////////////////////////////////////////////
}
