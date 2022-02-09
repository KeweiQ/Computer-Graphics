#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////

  if (num_leaves == 0) {
    this->left = NULL;
    this->right = NULL;

  } else if (num_leaves == 1) {
    this->left = objects[0];
    this->right = NULL;
    insert_box_into_box(objects[0]->box, this->box);

  } else if (num_leaves == 2) {
    this->left = objects[0];
    this->right = objects[1];
    insert_box_into_box(objects[0]->box, this->box);
    insert_box_into_box(objects[1]->box, this->box);

  } else {
    // build a bounding box contains all objects (triangles)
    BoundingBox box_of_all = BoundingBox();
    for (int i=0; i<num_leaves; i++) {
      insert_box_into_box(objects[i]->box, box_of_all);
    }

    // calculate midpoint along the longest axis
    int axis = 0;
    double longest = -1;
    for (int i=0; i<3; i++) {
      double length = box_of_all.max_corner(i) - box_of_all.min_corner(i);
      if (length > longest) {
        longest = length;
        axis = i;
      }
    }
    int midpoint = box_of_all.center()(axis);

    // saperate original object list into 2 sublists according to midpoint
    std::vector<std::shared_ptr<Object>> left_objects;
    std::vector<std::shared_ptr<Object>> right_objects;
    int center;
    for (int i=0; i<num_leaves; i++) {
      center = objects[i]->box.center()[axis];
      if (center <= midpoint) {
        left_objects.push_back(objects[i]);
      } else {
        right_objects.push_back(objects[i]);
      }
    }

    // make sure sublist it not the same as the original object list
    if (left_objects.size() != 0 && right_objects.size() == 0){
      right_objects.push_back(left_objects.back());
      left_objects.pop_back();
    }
    else if (left_objects.size() == 0 && right_objects.size() != 0){
      left_objects.push_back(right_objects.back());
      right_objects.pop_back();
    }

    // construct left subtree and right subtree
    this->left = std::make_shared<AABBTree>(left_objects, a_depth + 1);
    this->right = std::make_shared<AABBTree>(right_objects, a_depth + 1);

    // update bonding box by inserting subtrees' boxes
    insert_box_into_box(this->left->box, this->box);
    insert_box_into_box(this->right->box, this->box);
  }

  ////////////////////////////////////////////////////////////////////////////
}
