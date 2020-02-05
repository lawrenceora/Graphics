#include <cmath>

BoundingBoxTree::BoundingBoxTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  // Intialize box attribute
  for (int j = 0; j < objects.size(); j++){
    insert_box_into_box(objects[j]->box, box);
  }

  // Base cases.
  if (objects.size() == 0){
    left = NULL;
    right = NULL;
  } else if (objects.size() == 1){
    left = objects[0];
    right = NULL;
  } else if (objects.size() == 2){
    left = objects[0];
    right = objects[1];

  // Divide objects based on centre of longest split.
  } else {
    // Find coordinate and value of the midpoint.
    std::vector<std::shared_ptr<Object>> left_objects, right_objects;
    double mx, my, mz, midpoint;
    int split_i;
    mx = std::abs(box.max_corner(0) - box.min_corner(0));
    my = std::abs(box.max_corner(1) - box.min_corner(1));
    mz = std::abs(box.max_corner(2) - box.min_corner(2));
    if (mx > my && mx > mz){
      split_i = 0;
    } else if (my > mz && my > mx){
      split_i = 1;
    } else {
      split_i = 2;
    }
    midpoint = box.center()[split_i];

    // Split objects into left and right nodes;
    for (int i = 0; i < objects.size(); i++){
      if (objects[i]->box.center()[split_i] < midpoint){
        left_objects.push_back(objects[i]);
      } else {
        right_objects.push_back(objects[i]);
      }
    }
    
    // Prevent possibility of infinite recursion:
    if (left_objects.size() > 2 && right_objects.size() == 0){
      right_objects.push_back(left_objects.back());
      left_objects.pop_back();
    } else if (right_objects.size() > 2 && left_objects.size() == 0){
      left_objects.push_back(right_objects.back());
      right_objects.pop_back();
    }


    std::shared_ptr<Object> l = std::make_shared<BoundingBoxTree>(BoundingBoxTree(left_objects, a_depth + 1));
    std::shared_ptr<Object> r = std::make_shared<BoundingBoxTree>(BoundingBoxTree(right_objects, a_depth + 1));
    
    left = l;
    right = r;
  }

}
