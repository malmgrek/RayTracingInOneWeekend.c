#include "ray.h"

vec3_t ray_at(ray_t ray, double t) {
  vec3_t u = add(ray.origin, mul(t, ray.direction));
  return u;
}
