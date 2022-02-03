#ifndef VEC3_H_
#define VEC3_H_

#include <math.h>
#include <stdarg.h>

#include "utils.h"

typedef struct {
  double x;
  double y;
  double z;
} vec3_t;

vec3_t Vector(double x, double y, double z);
vec3_t Point(double x, double y, double z);

// New, faster implementations
double dot2(vec3_t *u, vec3_t *v);
vec3_t mul2(double t, vec3_t *u);
vec3_t add2(vec3_t *u, vec3_t *v);
vec3_t sub2(vec3_t *u, vec3_t *v);
vec3_t unit_vector2(vec3_t *u);
vec3_t cross2(vec3_t *u, vec3_t *v);

// Basic linear space operations
double dot(vec3_t u, vec3_t v);
double norm(vec3_t u);
double norm_squared(vec3_t u);
vec3_t add(vec3_t u, vec3_t v);
vec3_t cross(vec3_t u, vec3_t v);
vec3_t emul(vec3_t u, vec3_t v);
vec3_t mul(double t, vec3_t u);
vec3_t reflect(vec3_t *u, vec3_t *n);
vec3_t refract(vec3_t *uv, vec3_t *n, double etai_over_etat);
vec3_t sub(vec3_t u, vec3_t v);

// Utility functions
bool near_zero(vec3_t *u);
vec3_t random_in_unit_disk();
vec3_t random_in_unit_sphere();
vec3_t random_on_unit_sphere();
vec3_t random_vector(double min, double max);
vec3_t random_vector_unit();
vec3_t unit_vector(vec3_t *direction);
void print_vector(vec3_t u);

#endif // VEC3_H_
