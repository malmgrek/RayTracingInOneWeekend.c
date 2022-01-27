#ifndef HITTABLE_H_
#define HITTABLE_H_

#include <stdbool.h>

#include "ray.h"

typedef struct {
  // REVIEW: Does this need to be pointer, so that sphere_hit can modify it through
  // top level pointer?
  vec3_t center;
  double radius;
  // Generic "hittable" attributes
  vec3_t p;
  vec3_t normal;
  double t;
  bool front_face;
} sphere_t;

bool sphere_hit(sphere_t *sphere, const ray_t ray, double t_min, double t_max);

#endif // HITTABLE_H_
