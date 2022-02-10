#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list>

typedef std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> lst_element;

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////

  std::list<lst_element> lst;
  if (box_box_intersect(rootA->box, rootB->box)) {
    lst.push_back(std::make_pair(rootA, rootB));
  }

  while (lst.size() > 0) {
    lst_element e = lst.front();
    lst.pop_front();
    std::shared_ptr<AABBTree> nodeA = std::dynamic_pointer_cast<AABBTree>(e.first);
    std::shared_ptr<AABBTree> nodeB = std::dynamic_pointer_cast<AABBTree>(e.second);

    // nodeA and nodeB are both leaves
    if (!nodeA && !nodeB) {
      leaf_pairs.push_back(std::make_pair(e.first, e.second));

    // nodeA is a leaf, nodeB is a subtree
    } else if (!nodeA) {
      if (nodeB->left && box_box_intersect(e.first->box, nodeB->left->box)) {
        lst.push_back(std::make_pair(e.first, nodeB->left));
      }
      if (nodeB->right && box_box_intersect(e.first->box, nodeB->right->box)) {
        lst.push_back(std::make_pair(e.first, nodeB->right));
      }

    // nodeA is a subtree, nodeB is a leaf
    } else if (!nodeB) {
      if (nodeA->left && box_box_intersect(nodeA->left->box, e.second->box)) {
        lst.push_back(std::make_pair(nodeA->left, e.second));
      }
      if (nodeA->right && box_box_intersect(nodeA->right->box, e.second->box)) {
        lst.push_back(std::make_pair(nodeA->right, e.second));
      }
    
    // nodeA and nodeB are both subtrees
    } else {
      if (nodeA->left && nodeB->left && box_box_intersect(nodeA->left->box, nodeB->left->box)) {
        lst.push_back(std::make_pair(nodeA->left, nodeB->left));
      }
      if (nodeA->left && nodeB->right && box_box_intersect(nodeA->left->box, nodeB->right->box)) {
        lst.push_back(std::make_pair(nodeA->left, nodeB->right));
      }
      if (nodeA->right && nodeB->left && box_box_intersect(nodeA->right->box, nodeB->left->box)) {
        lst.push_back(std::make_pair(nodeA->right, nodeB->left));
      }
      if (nodeA->right && nodeB->right && box_box_intersect(nodeA->right->box, nodeB->right->box)) {
        lst.push_back(std::make_pair(nodeA->right, nodeB->right));
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}
