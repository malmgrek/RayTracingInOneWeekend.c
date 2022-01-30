#include "hittable.h"

bool sphere_hit(hit_record_t *rec,
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

  rec->t = root;
  rec->p = ray_at(ray, root);
  rec->normal = mul(1 / sphere.radius,
                    sub(rec->p, sphere.center));

  vec3_t outward_normal = mul(1 / sphere.radius,
                              sub(rec->p, sphere.center));
  rec->front_face = dot(ray.direction, outward_normal) < 0.0;
  rec->normal = rec->front_face ?
    outward_normal : mul(-1.0, outward_normal);


  // Count as hit if all ok
  rec->count += 1;

  return true;

}

hit_record_t hit(const ray_t ray, world_t world) {
  // TODO / FIXME: Ugly mutative function, could we improve sphere_hit?
  hit_record_t *acc = calloc(1, sizeof(hit_record_t));
  acc->t = 1.0e12;
  acc->count = 0;
  for (int i = 0; i < world.num_spheres; ++i) {
    sphere_hit(acc, world.spheres[i], ray, 0.0, acc->t);
  }
  hit_record_t rec = *acc;
  free(acc);
  return rec;
}
