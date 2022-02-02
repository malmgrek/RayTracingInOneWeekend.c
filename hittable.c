#include "hittable.h"

material_t Material(double ir, double fuzz, vec3_t albedo, int class) {
  material_t mat;
  mat.index_of_refraction = ir;
  mat.fuzz = fuzz;
  mat.albedo = albedo;
  mat.class = class;
  return mat;
}

sphere_t Sphere(vec3_t center, double radius, material_t material) {
  sphere_t sp;
  sp.center = center;
  sp.radius = radius;
  sp.material = material;
  return sp;
}

bool sphere_hit(hit_record_t *rec,
                sphere_t sphere,
                ray_t *ray,
                double t_min,
                double t_max) {

  vec3_t oc = sub(ray->origin, sphere.center);
  double a = norm_squared(ray->direction);
  double half_b = dot(oc, ray->direction);
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
  rec->normal = mul(1.0 / sphere.radius,
                    sub(rec->p, sphere.center));

  vec3_t outward_normal = mul(1.0 / sphere.radius,
                              sub(rec->p, sphere.center));
  rec->front_face = dot(ray->direction, outward_normal) < 0.0;
  rec->normal = rec->front_face ?
    outward_normal : mul(-1.0, outward_normal);
  rec->material = sphere.material;

  // Count as hit if all ok
  rec->count += 1;

  return true;

}

void hit(hit_record_t *rec, ray_t *ray, world_t *world) {
  rec->t = 1.0e12;  // = INFINITY
  rec->count = 0;
  for (int i = 0; i < world->num_spheres; ++i) {
    // NOTE: Adding non-zero t_min has a huge effect on the image
    // darkness
    sphere_hit(rec, world->spheres[i], ray, 1.0e-3, rec->t);
  }
}

bool scatter_dielectric(ray_t *ray_in,
                        hit_record_t *rec,
                        color_t *attenuation,
                        ray_t *scattered) {
  attenuation->x = 1.0;
  attenuation->y = 1.0;
  attenuation->z = 1.0;
  double ir = rec->material.index_of_refraction;
  double refraction_ratio = rec->front_face ? (1.0 / ir) : ir;
  vec3_t unit_direction = unit_vector(&ray_in->direction);

  double cos_theta = fmin(dot(mul(-1.0, unit_direction), rec->normal), 1.0);
  double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
  bool cannot_refract = refraction_ratio * sin_theta > 1.0;
  vec3_t direction;
  if (cannot_refract ||
      reflectance(cos_theta, refraction_ratio) > random_double_unit()) {
    direction = reflect(unit_direction, rec->normal);
  } else {
    direction = refract(unit_direction, rec->normal, refraction_ratio);
  }

  scattered->origin = rec->p;
  scattered->direction = direction;
  return true;
}

bool scatter_lambertian(hit_record_t *rec,
                        color_t *attenuation,
                        ray_t *scattered) {
  vec3_t scatter_direction = add(rec->normal, random_on_unit_sphere());

  // Catch degenerate scatter direction
  if (near_zero(scatter_direction)) {
    scatter_direction = rec->normal;
  }

  scattered->origin = rec->p;
  scattered->direction = scatter_direction;
  *attenuation = rec->material.albedo;
  return true;
}

bool scatter_metal(ray_t *ray_in,
                   hit_record_t *rec,
                   color_t *attenuation,
                   ray_t *scattered) {
  vec3_t reflected = reflect(unit_vector(&ray_in->direction), rec->normal);
  scattered->origin = rec->p;
  scattered->direction = add(reflected,
                             mul(rec->material.fuzz,
                                 random_in_unit_sphere()));
  *attenuation = rec->material.albedo;
  return (dot(reflected, rec->normal) > 0.0);
}

// Wrapper function for all different scatterings
bool scatter(ray_t *ray_in,
             hit_record_t *rec,
             color_t *attenuation,
             ray_t *scattered) {
  if (rec->material.class == 1) {
    return scatter_lambertian(rec, attenuation, scattered);
  }
  if (rec->material.class == 2) {
    return scatter_metal(ray_in, rec, attenuation, scattered);
  }
  if (rec->material.class == 3) {
    return scatter_dielectric(ray_in, rec, attenuation, scattered);
  }
  return false;
}

void destroy_world(world_t *world) {
  free(world->spheres);
  free(world);
}
