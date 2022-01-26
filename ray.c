#include "ray.h"

vec3_t ray_at(ray_t r, double t) {
  vec3_t u = add(r.origin, mul(t, r.direction));
  return u;
}
