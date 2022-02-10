#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  
  // intersect with curreent box
  if (ray_intersect_box(ray, this->box, min_t, max_t)) {
    // check ray intersection with 2 subtrees
    double t_left, t_right;
    std::shared_ptr<Object> des_left, des_right;
    bool intersect_left = false;
    bool intersect_right = false;
    std::shared_ptr<Object> left_sub = this->left;
    std::shared_ptr<Object> right_sub = this->right;
    
    if (this->left) {
      intersect_left = left_sub->ray_intersect(ray, min_t, max_t, t_left, des_left);
    }
    if (this->right) {
      intersect_right = right_sub->ray_intersect(ray, min_t, max_t, t_right, des_right);
    }

    // child node is leaf
    if (intersect_left && !des_left) {
      des_left = this->left;
    }
    if (intersect_right && !des_right) {
      des_right = this->right;
    }
    
    // intersection in both subtrees
    if (intersect_left && intersect_right) {
      if (t_left < t_right) {
        t = t_left;
        descendant = des_left;
      } else {
        t = t_right;
        descendant = des_right;
      }
      return true;

    // intersection in left subtree
    } else if (intersect_left) {
      t = t_left;
      descendant = des_left;
      return true;

    // intersection in right subtree
    } else if (intersect_right) {
      t = t_right;
      descendant = des_right;
      return true;
    
    // intersection in neither of subtree
    } else {
      return false;
    }
    // }
  
  // not intersect with curreent box
  } else {
    return false;
  }

  ////////////////////////////////////////////////////////////////////////////
}
