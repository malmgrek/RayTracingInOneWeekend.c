#ifndef RAY_H_
#define RAY_H_

#include "vec3.h"

typedef struct {
  vec3_t origin;
  vec3_t direction;
} ray_t;

vec3_t ray_at(ray_t *ray, double t);

#endif // RAY_H_
