bool BoundingBoxTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  bool temp_hit[2] = {false};
  double temp_t[2] = {0};
  std::shared_ptr<Object> temp_descendant[2] = {NULL};
  std::shared_ptr<Object> children[2] = {left, right};

  if (!ray_intersect_box(ray, box, min_t, max_t)){
    return false;
  }

  // Check if children is an primitive or BoundingBoxT, then check for hit
  for (int i = 0; i < 2; i++){
    if (children[i] != NULL){
      std::shared_ptr<BoundingBoxTree> bbt = std::dynamic_pointer_cast<BoundingBoxTree>(children[i]);
      temp_hit[i] = children[i]->ray_intersect(ray, min_t, max_t, temp_t[i], temp_descendant[i]);
        if (!bbt && temp_hit[i]){
          temp_descendant[i] = children[i];
        }
    }
  }

  // Return closest hit, or false if no hit
  if (!temp_hit[0] && !temp_hit[1]){
    return false;
  } else if (temp_hit[0] && !temp_hit[1]){
    t = temp_t[0];
    descendant = temp_descendant[0];
  } else if (!temp_hit[0] && temp_hit[1]){
    t = temp_t[1];
    descendant = temp_descendant[1];
  } else {
    if (temp_t[0] < temp_t[1]){
      t = temp_t[0];
      descendant = temp_descendant[0];
    } else {
      t = temp_t[1];
      descendant = temp_descendant[1];
    }
  }

  return true;
}

