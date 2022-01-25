#ifndef VEC3_H_
#define VEC3_H_

#include <math.h>
#include <stdio.h>

typedef struct {
  double x;
  double y;
  double z;
} Vec3;

typedef Vec3 Point3;

// Basic linear space operations
Vec3 add(Vec3 u, Vec3 v);
Vec3 lmul(double t, Vec3 u);
Vec3 rmul(Vec3 u, double t);
Vec3 ldiv(double t, Vec3 u);
Vec3 rdiv(Vec3 u, double t);
double length(Vec3 u);
double length_squared(Vec3 u);

// Utility functions
void print_vector(Vec3 u);
double dot(Vec3 u, Vec3 v);
Vec3 cross(Vec3 u, Vec3 v);
Vec3 unit_vector(Vec3 u, Vec3 direction);

#endif // VEC3_H_
