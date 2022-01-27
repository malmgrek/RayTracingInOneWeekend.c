#ifndef HITTABLE_H_
#define HITTABLE_H_

#include <stdbool.h>

#include "ray.h"

typedef struct {
  vec3_t p;
  vec3_t normal;
  double t;
  bool front_face;
} hittable_t;

typedef struct {
  // REVIEW: Does this need to be pointer, so that sphere_hit can modify it through
  // top level pointer?
  hittable_t hittable;
  vec3_t center;
  double radius;
} sphere_t;

void set_face_normal(hittable_t *hittable,
                     const ray_t ray,
                     const vec3_t outward_normal);
bool sphere_hit(sphere_t *sphere, const ray_t ray, double t_min, double t_max);

#endif // HITTABLE_H_
