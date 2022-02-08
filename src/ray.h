#ifndef RAY_H_
#define RAY_H_

#include "vec3.h"

typedef struct {
  vec3_t origin;
  vec3_t direction;
} ray_t;

static inline vec3_t ray_at(const ray_t *ray, double t) {
  vec3_t t_dir = mul(t, &ray->direction);
  return add(&ray->origin, &t_dir);
}

#endif // RAY_H_
