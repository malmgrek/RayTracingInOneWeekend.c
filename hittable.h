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

typedef struct {
  sphere_t *spheres;
  int num_spheres;
} world_t;

bool sphere_hit(hit_record_t *red,
                sphere_t sphere,
                const ray_t ray,
                double t_min,
                double t_max);

hit_record_t hit(const ray_t ray, world_t world);

// NOTE: Define other shapes by defining type & hit-function pairs

#endif // HITTABLE_H_
