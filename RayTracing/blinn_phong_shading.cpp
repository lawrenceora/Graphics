#include <iostream>
#include <cmath>
#define FUDGE 0.001

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector<std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  Eigen::Vector3d I, l, h, shadow_n;
  Eigen::Vector3d rgb = Eigen::Vector3d(0,0,0);
  Eigen::Vector3d Ia = Eigen::Vector3d(0.1,0.1,0.1);
  Eigen::Vector3d v = - ray.direction.normalized();
  Eigen::Vector3d q = ray.origin + t*ray.direction;
  Eigen::Vector3d ka = objects[hit_id]->material->ka;
  Eigen::Vector3d kd = objects[hit_id]->material->kd;
  Eigen::Vector3d ks = objects[hit_id]->material->ks;
  double nl_angle, nh_angle, max_t, shadow_t;
  double p = objects[hit_id]->material->phong_exponent;
  int shadow_hit_id;
  Ray shadowray;

  // Add Ambient Shading
  rgb = (ka.array() * Ia.array()).matrix();
  
  for (int i = 0; i < lights.size(); i++){
    // Check if point is in the light's shadow
    lights[i]->direction(q, l, max_t);
    shadowray.origin = q;
    shadowray.direction = l; 

    bool in_shadow = first_hit(shadowray, FUDGE, objects, shadow_hit_id, shadow_t, shadow_n);
    
    if (!in_shadow || shadow_t > max_t){   
      I = lights[i]->I;
       
      // Add Lambertian Shading
      nl_angle = (n.dot(l) > 0) ? n.dot(l) : 0;
      rgb += (kd.array() * I.array()).matrix() * nl_angle;

      // Add Blinn-Phong Shading
      h = (v+l).normalized();
      nh_angle = (n.dot(h) > 0) ? n.dot(h) : 0;
      rgb += (ks.array() * I.array()).matrix() * std::pow(nh_angle, p);
    }
  }
  
  return rgb; 

}
