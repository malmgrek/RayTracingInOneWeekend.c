#include "camera.h"

ray_t get_ray(camera_t camera, double u, double v) {
  ray_t ray;
  ray.origin = camera.origin;
  // direction = lower_left_corner + u * horizontal + v * vertical - origin
  ray.direction = add(add(camera.lower_left_corner,
                          mul(u, camera.horizontal)),
                      sub(mul(v, camera.vertical),
                          camera.origin));
  return ray;
}

camera_t create_default_camera() {
  camera_t cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.viewport_height = 2.0;
  cam.viewport_width = cam.aspect_ratio * cam.viewport_height;
  cam.focal_length = 1.0;
  vec3_t focal = { 0.0, 0.0, cam.focal_length };
  vec3_t origin = { 0.0, 0.0, 0.0 };
  cam.origin = origin;
  vec3_t horizontal = { cam.viewport_width, 0.0, 0.0 };
  cam.horizontal = horizontal;
  vec3_t vertical = { 0.0, cam.viewport_height, 0.0 };
  cam.vertical = vertical;
  // origin - horizontal/2 - vertical/2 - focal
  vec3_t lower_left_corner = sub(sub(cam.origin, mul(0.5, cam.horizontal)),
                               add(mul(0.5, cam.vertical), focal));
  cam.lower_left_corner = lower_left_corner;
  return cam;
}
