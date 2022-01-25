#include "vec3.h"

double norm_squared(Vec3 u) {
  double t = u.x * u.x + u.y * u.y + u.z * u.z;
  return t;
}

double norm(Vec3 u) {
  double t = sqrt(norm_squared(u));
  return t;
}

Vec3 unit_vector(Vec3 direction) {
  double t = norm(direction);
  Vec3 v = { direction.x / t, direction.y / t, direction.z / t };
  return v;
}

Vec3 mul(double t, Vec3 u) {
  Vec3 v = { t * u.x, t * u.y, t * u.z };
  return v;
}

Vec3 add(Vec3 u, Vec3 v) {
  Vec3 w = { u.x + v.x, u.y + v.y, u.z + v.z };
  return w;
}

Vec3 sub(Vec3 u, Vec3 v) {
  Vec3 w = { u.x - v.x, u.y - v.y, u.z - v.z };
  return w;
}

double dot(Vec3 u, Vec3 v) {
  double t = u.x * v.x + u.y * v.y + u.z * v.z;
  return t;
}
