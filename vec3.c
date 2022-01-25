#include "vec3.h"

Vec3 unit_vector(Vec3 u, Vec3 direction) {
  double norm = sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));
  u.x = direction.x / norm;
  u.y = direction.y / norm;
  u.z = direction.z / norm;
  return u;
}

Vec3 lmul(double t, Vec3 u) {
  Vec3 res = { t * u.x, t * u.y, t * u.z };
  u = res;
  return u;
}


Vec3 add(Vec3 u, Vec3 v) {
  u.x = u.x + v.x;
  u.y = u.y + v.y;
  u.z = u.z + v.z;
  return u;
}
