#ifndef CAMERA_H_
#define CAMERA_H_

#include "vec3.h"
#include "ray.h"

typedef struct {
  vec3_t origin;
  vec3_t horizontal;
  vec3_t vertical;
  vec3_t lower_left_corner;
} camera_t;

camera_t create_camera(double vfov, double aspect_ratio);
ray_t get_ray(camera_t cam, double u, double v);

#endif // CAMERA_H_
