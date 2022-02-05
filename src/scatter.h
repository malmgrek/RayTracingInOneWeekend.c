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

hit_record_t HitRecord(vec3_t p,
                       vec3_t normal,
                       double t,
                       bool front_face,
                       int count,
                       material_t material);

material_t Material(double ir, double fuzz, vec3_t albedo, int class);

sphere_t Sphere(vec3_t center, double radius, material_t material);

world_t World(sphere_t *spheres, int num_spheres);

// ------------- Hit checking ----------------------

bool sphere_hit(hit_record_t *red,
                sphere_t *sphere,
                ray_t *ray,
                double t_min,
                double t_max);


void hit(hit_record_t *rec, ray_t *ray, world_t *world);

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
