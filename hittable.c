#include "hittable.h"

// NOTE: t_min = 0, t_max = INFINITY
bool sphere_hit(sphere_t *sphere, const ray_t ray, double t_min, double t_max) {

  vec3_t oc = sub(ray.origin, sphere->center);
  double a = norm_squared(ray.direction);
  double half_b = dot(oc, ray.direction);
  double c = norm_squared(oc) - sphere->radius * sphere->radius;

  double discr = half_b * half_b - a * c;
  if (discr < 0) {
    return false;
  }
  double sqrtd = sqrt(discr);

  // Find the nearest root that lies in the acceptable range
  double root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root)
      return false;
  }

  sphere->hittable.t = root;
  sphere->hittable.p = ray_at(ray, sphere->hittable.t);
  sphere->hittable.normal = mul(1 / sphere->radius,
                                sub(sphere->hittable.p, sphere->center));

  vec3_t outward_normal = mul(1 / sphere->radius,
                              sub(sphere->hittable.p, sphere->center));
  set_face_normal(&sphere->hittable, ray, outward_normal);

  return true;

}

void set_face_normal(hittable_t *hittable,
                     const ray_t ray,
                     const vec3_t outward_normal) {
  hittable->front_face = dot(ray.direction, outward_normal) < 0.0;
  hittable->normal = hittable->front_face ?
    outward_normal : mul(-1.0, outward_normal);
}
