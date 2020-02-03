void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{

  double a = (camera.width/width)*(width/2 - 0.5 - j);
  double b = (camera.height/height)*(height/2 - 0.5 - i);

  ray.origin = camera.e;
  ray.direction = b*camera.v - a*camera.u - camera.d*camera.w;
}

