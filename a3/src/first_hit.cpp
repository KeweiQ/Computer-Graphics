#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////

  double minimum = std::numeric_limits<double>::infinity();;
  bool found = false;
  double t_temp;
  Eigen::Vector3d n_temp;
  
  for (int i=0; i<objects.size(); i++) {
    std::shared_ptr<Object> object = objects[i];
    bool inter = object->intersect(ray, min_t, t_temp, n_temp);
   
    if (inter) {
      found = true;
      if (t_temp < minimum) {
        hit_id = i;
        minimum = t_temp;
        t = t_temp;
        n = n_temp;
      }
    }
  }

  return found;
  
  ////////////////////////////////////////////////////////////////////////////
}
