#ifndef CAMERA_H_
#define CAMERA_H_

#include "vec3.h"
#include "ray.h"

typedef struct {
  double aspect_ratio;
  double viewport_height;
  double viewport_width;
  double focal_length;
  vec3_t origin;
  vec3_t horizontal;
  vec3_t vertical;
  vec3_t lower_left_corner;
} camera_t;

camera_t create_default_camera();
ray_t get_ray(camera_t camera, double u, double v);

#endif // CAMERA_H_
