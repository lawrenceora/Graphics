bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  Eigen::Vector3d abc = A.transpose() - B.transpose();
  Eigen::Vector3d def = A.transpose() - C.transpose();
  Eigen::Vector3d ghi = ray.direction;
  Eigen::Vector3d jkl = A.transpose() - ray.origin;

  double ei_minus_hf = def(1)*ghi(2) - ghi(1)*def(2);
  double gf_minus_di = ghi(0)*def(2) - def(0)*ghi(2);
  double dh_minus_eg = def(0)*ghi(1) - def(1)*ghi(0);
  double ak_minus_jb = abc(0)*jkl(1) - jkl(0)*abc(1);
  double jc_minus_al = jkl(0)*abc(2) - abc(0)*jkl(2);
  double bl_minus_kc = abc(1)*jkl(2) - jkl(1)*abc(2);

  double m = abc(0)*ei_minus_hf + abc(1)*gf_minus_di + abc(2)*dh_minus_eg;
  double theta = - (def(2)*ak_minus_jb + def(1)*jc_minus_al + def(0)*bl_minus_kc) / m;
  if (theta < min_t || theta > max_t){
    return false;
  }

  double gamma = (ghi(2)*ak_minus_jb + ghi(1)*jc_minus_al + ghi(0)*bl_minus_kc) / m;
  if (gamma < 0 || gamma > 1){
    return false;
  }

  double beta = (jkl(0)*ei_minus_hf + jkl(1)*gf_minus_di + jkl(2)*dh_minus_eg) / m;
  if (beta < 0 || beta > 1 - gamma){
    return false;
  }
  
  t = theta;
  return true;  


}

