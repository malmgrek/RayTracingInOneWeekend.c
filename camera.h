#ifndef CAMERA_H_
#define CAMERA_H_

#include "vec3.h"
#include "ray.h"

typedef struct {
  vec3_t origin;
  vec3_t horizontal;
  vec3_t vertical;
  vec3_t lower_left_corner;
  vec3_t u;
  vec3_t v;
  vec3_t w;
  double lens_radius;
} camera_t;

camera_t Camera(vec3_t lookfrom,
                vec3_t lookat,
                vec3_t vup,
                double vfov,
                double aspect_ratio,
                double aperture,
                double focus_dist);

void set_ray(ray_t *ray, camera_t *cam, double s, double t);

#endif // CAMERA_H_
