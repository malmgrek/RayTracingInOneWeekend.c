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

typedef vec3_t Point3;

// Basic linear space operations
vec3_t add(vec3_t u, vec3_t v);
vec3_t sub(vec3_t u, vec3_t v);
vec3_t mul(double t, vec3_t u);
double norm(vec3_t u);
double norm_squared(vec3_t u);

// Utility functions
void print_vector(vec3_t u);
double dot(vec3_t u, vec3_t v);
vec3_t cross(vec3_t u, vec3_t v);
vec3_t unit_vector(vec3_t direction);
vec3_t random_vector_unit();
vec3_t random_vector(double min, double max);
vec3_t random_in_unit_sphere();

#endif // VEC3_H_
