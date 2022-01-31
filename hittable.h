#ifndef HITTABLE_H_
#define HITTABLE_H_

#include "color.h"
#include "ray.h"
#include "utils.h"

typedef struct {
  double fuzz;
  color_t albedo;
  // 1: Lambertian
  // 2: Metal
  int class;
} material_t;

typedef struct {
  vec3_t center;
  double radius;
  material_t material;
} sphere_t;

typedef struct {
  sphere_t *spheres;
  int num_spheres;
} world_t;

typedef struct {
  vec3_t p;
  vec3_t normal;
  double t;
  bool front_face;
  int count;
  material_t material;
} hit_record_t;

bool sphere_hit(hit_record_t *red,
                sphere_t sphere,
                const ray_t ray,
                double t_min,
                double t_max);

hit_record_t hit(const ray_t ray, world_t world);

bool scatter_lambertian(hit_record_t rec,
                        color_t *attenuation,
                        ray_t *scattered);
bool scatter_metal(ray_t ray_in,
                   hit_record_t rec,
                   color_t *attenuation,
                   ray_t *scattered);
bool scatter(ray_t ray_in,
             hit_record_t rec,
             color_t *attenuation,
             ray_t *scattered);

// NOTE: Define other shapes by defining type & hit-function pairs

#endif // HITTABLE_H_
