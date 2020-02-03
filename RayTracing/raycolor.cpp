#define MAX_RECURSIVE 5
#define FUDGE 0.001

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  int hit_id;
  double t;
  Eigen::Vector3d n;

  if (!first_hit(ray, min_t, objects, hit_id, t, n)){
    return false;
  }
  
  // Return black light if max recursive depth reached. 
  if (num_recursive_calls > MAX_RECURSIVE){
    rgb = Eigen::Vector3d(0,0,0);
    return true;
  }

  // Get blinn phong shading
  rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
  
  //Do a recusive call if surface is reflective
  Eigen::Vector3d km = objects[hit_id]->material->km;
  if (!km.isZero()){
    Ray reflected;
    reflected.direction = reflect(ray.direction.normalized(), n);
    reflected.origin = ray.origin + t*ray.direction;
    Eigen::Vector3d mirror_color;
    if (raycolor(reflected, FUDGE, objects, lights, num_recursive_calls + 1, mirror_color)){
        rgb += (km.array() * mirror_color.array()).matrix();
    }
  }

  return true;
}
