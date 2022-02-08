#include "scatter.h"

bool sphere_hit(hit_record_t *rec,
                const sphere_t *sphere,
                const ray_t *ray,
                double t_min,
                double t_max) {

  vec3_t oc = sub(&ray->origin, &sphere->center);
  double a = dot(&ray->direction, &ray->direction);
  double half_b = dot(&oc, &ray->direction);
  double c = dot(&oc, &oc) - sphere->radius * sphere->radius;
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
  vec3_t temp = sub(&rec->p, &sphere->center);
  rec->normal = mul(1 / sphere->radius, &temp);
  rec->front_face = dot(&ray->direction, &rec->normal) < 0.0;

  if (!rec->front_face) {
    rec->normal = mul(-1.0, &rec->normal);
  }

  rec->material = sphere->material;
  rec->count += 1;  // Count as hit if all ok

  return true;

}

void hit(hit_record_t *rec, const ray_t *ray, const world_t *world) {
  rec->t = INFINITY;
  rec->count = 0;
  for (int i = 0; i < world->num_spheres; ++i) {
    // NOTE: Adding non-zero t_min has a huge effect on the image
    // darkness
    sphere_hit(rec, &world->spheres[i], ray, 1.0e-3, rec->t);
  }
}

bool scatter_dielectric(color_t *attenuation,
                        ray_t *scattered,
                        const ray_t *ray_in,
                        const hit_record_t *rec) {
  attenuation->x = 1.0;
  attenuation->y = 1.0;
  attenuation->z = 1.0;
  double ir = rec->material.index_of_refraction;
  double refraction_ratio = rec->front_face ? (1.0 / ir) : ir;
  vec3_t unit_direction = unit_vector(&ray_in->direction);
  double cos_theta = fmin(-dot(&unit_direction, &rec->normal), 1.0);
  double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

  bool cannot_refract = refraction_ratio * sin_theta > 1.0;
  vec3_t direction;
  if (cannot_refract ||
      reflectance(cos_theta, refraction_ratio) > RANDOM_DOUBLE_UNIT) {
    direction = reflect(&unit_direction, &rec->normal);
  } else {
    direction = refract(&unit_direction, &rec->normal, refraction_ratio);
  }

  scattered->origin = rec->p;
  scattered->direction = direction;
  return true;
}

bool scatter_lambertian(color_t *attenuation,
                        ray_t *scattered,
                        const hit_record_t *rec) {
  vec3_t rand = random_on_unit_sphere();
  vec3_t scatter_direction = add(&rec->normal, &rand);

  // Catch degenerate scatter direction
  if (near_zero(&scatter_direction)) {
    scatter_direction = rec->normal;
  }

  scattered->origin = rec->p;
  scattered->direction = scatter_direction;
  *attenuation = rec->material.albedo;
  return true;
}

bool scatter_metal(color_t *attenuation,
                   ray_t *scattered,
                   const ray_t *ray_in,
                   const hit_record_t *rec) {

  vec3_t unit = unit_vector(&ray_in->direction);
  vec3_t reflected = reflect(&unit, &rec->normal);
  vec3_t rand = random_in_unit_sphere();
  vec3_t temp = mul(rec->material.fuzz, &rand);
  scattered->direction = add(&reflected, &temp);
  scattered->origin = rec->p;
  *attenuation = rec->material.albedo;

  return dot(&reflected, &rec->normal) > 0.0;

}

// Wrapper function for all different scatterings
bool scatter(color_t *attenuation,
             ray_t *scattered,
             const ray_t *ray_in,
             const hit_record_t *rec) {
  if (rec->material.class == 1) {
    return scatter_lambertian(attenuation, scattered, rec);
  }
  if (rec->material.class == 2) {
    return scatter_metal(attenuation, scattered, ray_in, rec);
  }
  if (rec->material.class == 3) {
    return scatter_dielectric(attenuation, scattered, ray_in, rec);
  }
  return false;
}

void destroy_world(world_t *world) {
  free(world->spheres);
  free(world);
}
