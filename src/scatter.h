#ifndef SCATTER_H_
#define SCATTER_H_

#include "color.h"
#include "ray.h"
#include "utils.h"

typedef struct {
  double index_of_refraction;
  double fuzz;
  color_t albedo;
  // 1: Lambertian
  // 2: Metal
  // 3: Dielectric
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

// -------------- Type instance constructors -------

static inline material_t Material(double ir, double fuzz, vec3_t albedo, int class) {
  material_t mat;
  mat.index_of_refraction = ir;
  mat.fuzz = fuzz;
  mat.albedo = albedo;
  mat.class = class;
  return mat;
}

static inline sphere_t Sphere(vec3_t center, double radius, material_t material) {
  sphere_t sp;
  sp.center = center;
  sp.radius = radius;
  sp.material = material;
  return sp;
}

// ------------- Hit checking ----------------------

bool sphere_hit(hit_record_t *red,
                const sphere_t *sphere,
                const ray_t *ray,
                double t_min,
                double t_max);


void hit(hit_record_t *rec, const ray_t *ray, const world_t *world);

// ------------- Scattering ------------------------

bool scatter_dielectric(ray_t *ray_in,
                        hit_record_t *rec,
                        color_t *attenuation,
                        ray_t *scattered);

bool scatter_lambertian(hit_record_t *rec,
                        color_t *attenuation,
                        ray_t *scattered);

bool scatter_metal(ray_t *ray_in,
                   hit_record_t *rec,
                   color_t *attenuation,
                   ray_t *scattered);

bool scatter(ray_t *ray_in,
             hit_record_t *rec,
             color_t *attenuation,
             ray_t *scattered);

void destroy_world(world_t *world);

#endif // SCATTER_H_
