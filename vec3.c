#include "vec3.h"

double dot(vec3_t u, vec3_t v) {
  double t = u.x * v.x + u.y * v.y + u.z * v.z;
  return t;
}

double norm_squared(vec3_t u) {
  return dot(u, u);
}

double norm(vec3_t u) {
  double t = sqrt(norm_squared(u));
  return t;
}

vec3_t unit_vector(vec3_t direction) {
  double t = norm(direction);
  vec3_t v = { direction.x / t, direction.y / t, direction.z / t };
  return v;
}

vec3_t random_vector_unit() {
  vec3_t u = { random_double_unit(), random_double_unit(), random_double_unit() };
  return u;
}

vec3_t random_vector(double min, double max) {
  vec3_t u = { random_double(min, max),
               random_double(min, max),
               random_double(min, max) };
  return u;
}

vec3_t random_in_unit_sphere() {
  vec3_t p = random_vector(-1, 1);
  if (norm_squared(p) < 1.0) {
    return p;
  } else {
    return random_in_unit_sphere();
  }
}

vec3_t mul(double t, vec3_t u) {
  vec3_t v = { t * u.x, t * u.y, t * u.z };
  return v;
}

vec3_t add(vec3_t u, vec3_t v) {
  vec3_t w = { u.x + v.x, u.y + v.y, u.z + v.z };
  return w;
}

vec3_t sub(vec3_t u, vec3_t v) {
  vec3_t w = { u.x - v.x, u.y - v.y, u.z - v.z };
  return w;
}
