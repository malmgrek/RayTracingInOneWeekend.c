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
  rec->material = sphere.material;

  // Count as hit if all ok
  rec->count += 1;

  return true;

}

hit_record_t hit(const ray_t ray, world_t world) {
  // TODO / FIXME: Ugly mutative function, could we improve sphere_hit?
  hit_record_t *acc = calloc(1, sizeof(hit_record_t));
  acc->t = 1.0e12;  // = INFINITY
  acc->count = 0;
  for (int i = 0; i < world.num_spheres; ++i) {
    // NOTE: Adding non-zero t_min has a huge effect on the image
    // darkness
    sphere_hit(acc, world.spheres[i], ray, 1.0e-3, acc->t);
  }
  hit_record_t rec = *acc;
  free(acc);
  return rec;
}

bool scatter_lambertian(hit_record_t rec,
                        color_t *attenuation,
                        ray_t *scattered) {
  vec3_t scatter_direction = add(rec.normal, random_on_unit_sphere());

  // Catch degenerate scatter direction
  if (near_zero(scatter_direction)) {
    scatter_direction = rec.normal;
  }

  scattered->origin = rec.p;
  scattered->direction = scatter_direction;
  *attenuation = rec.material.albedo;
  return true;
}

bool scatter_metal(ray_t ray_in,
                   hit_record_t rec,
                   color_t *attenuation,
                   ray_t *scattered) {
  vec3_t reflected = reflect(unit_vector(ray_in.direction), rec.normal);
  scattered->origin = rec.p;
  scattered->direction = reflected;
  *attenuation = rec.material.albedo;
  return (dot(reflected, rec.normal) > 0.0);
}

// Wrapper function for all different scatterings
bool scatter(ray_t ray_in,
             hit_record_t rec,
             color_t *attenuation,
             ray_t *scattered) {
  if (rec.material.class == 1) {
    return scatter_lambertian(rec, attenuation, scattered);
  }
  if (rec.material.class == 2) {
    return scatter_metal(ray_in, rec, attenuation, scattered);
  }
  return false;
}
