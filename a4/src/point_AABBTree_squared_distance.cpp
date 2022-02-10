#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include <utility>

typedef std::pair<double, std::shared_ptr<Object>> pq_element;
typedef std::pair<std::shared_ptr<Object>, double> queue_obj;

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////

  // initialize priority queue
  struct comparator {
    bool operator() (const pq_element & a, const pq_element & b) const
    {
      return a.first > b.first;
    }
  };
  std::priority_queue<pq_element, std::vector<pq_element>, comparator> pq;

  // initialize minimum distance
  double distance_min = std::numeric_limits<double>::infinity();

  // push root node into priority queue
  double distance_root  = point_box_squared_distance(query, root->box);
  if (distance_root >= min_sqrd && distance_root <= max_sqrd) {
    pq.push(std::make_pair(distance_root, root));
  } else {
    return false;
  }

  while (pq.size() > 0) { 
    // get distance of the top element in priority queue
    pq_element top = pq.top();
    pq.pop();
    double distance_top = top.first;
    std::shared_ptr<AABBTree> subtree = std::static_pointer_cast<AABBTree>(top.second);
    
    if (distance_top < distance_min) {
      // subtree has leaf child
      if (subtree->num_leaves <= 2) { // assured by construction method of AABB tree
        std::shared_ptr<Object> descendant_temp;
        double distance_temp;

        // check object on left child (if exists)
        if (subtree->left && subtree->left->point_squared_distance(query, min_sqrd, max_sqrd, distance_temp, descendant_temp)){
          if (distance_temp < distance_min){
            distance_min = distance_temp;
            descendant = subtree->left;
          }
        }

        // check object on right child (if exists)
        if (subtree->right && subtree->right->point_squared_distance(query, min_sqrd, max_sqrd, distance_temp, descendant_temp)){
          if (distance_temp < distance_min){
            distance_min = distance_temp;
            descendant = subtree->right;
          }
        }
      }

      // subtree has no leaf child
      else{
        double distance_left  = point_box_squared_distance(query, subtree->left->box);
        if (distance_left >= min_sqrd && distance_left <= max_sqrd) {
          pq.push(std::make_pair(distance_left, subtree->left));
        }

        double distance_right  = point_box_squared_distance(query, subtree->right->box);
        if (distance_right >= min_sqrd && distance_right <= max_sqrd) {
          pq.push(std::make_pair(distance_right, subtree->right));
        }
      }
    }
  }

  // check if find any distance in range
  if (descendant) {
    sqrd = distance_min;
    return true;
  } else {
    return false;
  }

  ////////////////////////////////////////////////////////////////////////////
}
