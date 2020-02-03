bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  bool found = false;
  double temp_t;
  Eigen::Vector3d temp_n;

  for(int i = 0; i < objects.size(); i++){
    if (objects[i]->intersect(ray, min_t, temp_t, temp_n) == true){
      if (found == false){
        found = true;
        t = temp_t;
        n = temp_n;
        hit_id = i;
      } else if (temp_t < t){
          t = temp_t;
          n = temp_n;
          hit_id = i;
      }
    }
  }

  return found;
}

