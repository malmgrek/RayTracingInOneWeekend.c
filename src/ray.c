#include "ray.h"

vec3_t ray_at(ray_t *ray, double t) {
  vec3_t u;
  u.x = ray->origin.x + t * ray->direction.x;
  u.y = ray->origin.y + t * ray->direction.y;
  u.z = ray->origin.z + t * ray->direction.z;
  return u;
}
