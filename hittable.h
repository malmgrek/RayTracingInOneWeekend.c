#ifndef HITTABLE_H_
#define HITTABLE_H_

#include <stdbool.h>

#include "ray.h"

typedef struct {
  vec3_t p;
  vec3_t normal;
  double t;
  bool front_face;
  int count;
} hit_record_t;

typedef struct {
  vec3_t center;
  double radius;
} sphere_t;

bool sphere_hit(hit_record_t *record,
                sphere_t sphere,
                const ray_t ray,
                double t_min,
                double t_max);

// NOTE: Define other shapes by defining type & hit-function pairs

#endif // HITTABLE_H_
