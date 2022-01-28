#include "hittable.h"

// NOTE: t_min = 0, t_max = INFINITY
bool sphere_hit(hit_record_t *record,
                sphere_t sphere,
                const ray_t ray,
                double t_min,
                double t_max) {

  vec3_t oc = sub(ray.origin, sphere.center);
  double a = norm_squared(ray.direction);
  double half_b = dot(oc, ray.direction);
  double c = norm_squared(oc) - sphere.radius * sphere.radius;

  double discr = half_b * half_b - a * c;
  if (discr < 0) {
    return false;
  }
  double sqrtd = sqrt(discr);

  // Find the nearest root that lies in the acceptable range
  double root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
  }
  if (root < t_min || t_max < root) {
    return false;
  }

  record->t = root;
  record->p = ray_at(ray, root);
  record->normal = mul(1 / sphere.radius,
                       sub(record->p, sphere.center));

  vec3_t outward_normal = mul(1 / sphere.radius,
                              sub(record->p, sphere.center));
  record->front_face = dot(ray.direction, outward_normal) < 0.0;
  record->normal = record->front_face ?
    outward_normal : mul(-1.0, outward_normal);


  // Count as hit if all ok
  record->count += 1;

  return true;

}
