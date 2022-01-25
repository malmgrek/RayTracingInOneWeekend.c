#ifndef VEC3_H_
#define VEC3_H_

#include <stdio.h>

typedef struct {
  double x;
  double y;
  double z;
} Vec3;

typedef Vec3 Point3;

// Basic linear space operations
Vec3 vec3_add(Vec3 *u, Vec3 *v);
Vec3 vec3_lmul(double t, Vec3 *u);
Vec3 vec3_rmul(Vec3 *u, double t);
Vec3 vec3_ldiv(double t, Vec3 *u);
Vec3 vec3_rdiv(Vec3 *u, double t);
double vec3_length(Vec3 u);
double vec3_length_squared(Vec3 u);

// Utility functions
void vec3_print(Vec3 *u);
double vec3_dot(Vec3 u, Vec3 v);
Vec3 vec3_cross(Vec3 *u, Vec3 *v);
Vec3 vec3_unit_vector(Vec3 *u);

#endif // VEC3_H_
