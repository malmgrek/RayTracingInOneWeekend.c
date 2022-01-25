#include "ray.h"

Vec3 ray_at(Ray r, double t) {
  Vec3 u = add(r.origin, mul(t, r.direction));
  return u;
}
