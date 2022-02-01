#include "camera.h"

ray_t get_ray(camera_t cam, double u, double v) {
  ray_t ray;
  ray.origin = cam.origin;
  // direction = lower_left_corner + u * horizontal + v * vertical - origin
  ray.direction = add(add(cam.lower_left_corner,
                          mul(u, cam.horizontal)),
                      sub(mul(v, cam.vertical),
                          cam.origin));
  return ray;
}

// Vfof: vertical field-of-view
camera_t create_camera(double vfov, double aspect_ratio) {
  double theta = degrees_to_radians(vfov);
  double h = tan(theta / 2.0);
  double viewport_height = 2.0 * h;
  double viewport_width = aspect_ratio * viewport_height;
  vec3_t focal = { 0.0, 0.0, 1.0 };
  vec3_t origin = { 0.0, 0.0, 0.0 };
  vec3_t horizontal = { viewport_width, 0.0, 0.0 };
  vec3_t vertical = { 0.0, viewport_height, 0.0 };
  vec3_t lower_left_corner = sub(sub(origin, mul(0.5, horizontal)),
                                 add(mul(0.5, vertical), focal));
  camera_t cam;
  cam.lower_left_corner = lower_left_corner;
  cam.horizontal = horizontal;
  cam.vertical = vertical;
  cam.origin = origin;
  return cam;
}
