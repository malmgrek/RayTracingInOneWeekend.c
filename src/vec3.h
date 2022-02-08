#ifndef VEC3_H_
#define VEC3_H_

#include <stdarg.h>

#include "utils.h"

typedef struct {
  double x;
  double y;
  double z;
} vec3_t;

static inline vec3_t Vector(double x, double y, double z) {
  vec3_t u = { x, y, z };
  return u;
}

static inline vec3_t Point(double x, double y, double z) {
  vec3_t u = { x, y, z };
  return u;
}

// New, faster implementations

static inline double dot(const vec3_t *u, const vec3_t *v) {
  return u->x * v->x + u->y * v->y + u->z * v->z;
}

static inline vec3_t mul(double t, const vec3_t *u) {
  vec3_t v = { t * u->x, t * u->y, t * u->z };
  return v;
}

static inline vec3_t add(const vec3_t *u, const vec3_t *v) {
  vec3_t w = { u->x + v->x, u->y + v->y, u->z + v->z };
  return w;
}

static inline vec3_t sub(const vec3_t *u, const vec3_t *v) {
  vec3_t w = { u->x - v->x, u->y - v->y, u->z - v->z };
  return w;
}

static inline vec3_t cross(const vec3_t *u, const vec3_t *v) {
  vec3_t w = { u->y * v->z - u->z * v->y,
               u->z * v->x - u->x * v->z,
               u->x * v->y - u->y * v->x };
  return w;
}

static inline vec3_t unit_vector(const vec3_t *direction) {
  // double t = norm(*direction);
  double t = sqrt(direction->x * direction->x +
                  direction->y * direction->y +
                  direction->z * direction->z);
  vec3_t v = { direction->x / t, direction->y / t, direction->z / t };
  return v;
}

static inline double norm(const vec3_t *u) {
  double t = sqrt(dot(u, u));
  return t;
}

static inline vec3_t elementwise_mul(const vec3_t *u, const vec3_t *v) {
  vec3_t w = { u->x * v->x, u->y * v->y, u->z * v->z };
  return w;
}

static inline vec3_t random_vector_unit() {
  vec3_t u = { RANDOM_DOUBLE_UNIT,
               RANDOM_DOUBLE_UNIT,
               RANDOM_DOUBLE_UNIT };
  return u;
}

static inline vec3_t random_vector(double min, double max) {
  vec3_t u = { RANDOM_DOUBLE(min, max),
               RANDOM_DOUBLE(min, max),
               RANDOM_DOUBLE(min, max) };
  return u;
}

static inline vec3_t random_in_unit_disk() {
  while (1) {
    vec3_t p = { RANDOM_DOUBLE(-1.0, 1.0), RANDOM_DOUBLE(-1.0, 1.0), 0.0 };
    if (dot(&p, &p) >= 1.0) continue;
    return p;
  }
}

static inline vec3_t random_in_unit_sphere() {
  while (1) {
    vec3_t p = random_vector(-1.0, 1.0);
    if (dot(&p, &p) >= 1.0) continue;
    return p;
  }
}

static inline vec3_t random_on_unit_sphere() {
  vec3_t p = random_in_unit_sphere();
  return unit_vector(&p);
}

// Basic linear space operations
static inline vec3_t reflect(const vec3_t *u, const vec3_t *n) {
  double t = dot(u, n);
  // vec3_t v = u - 2.0 * (u.n)n
  vec3_t v = {u->x - 2.0 * t * n->x,
               u->y - 2.0 * t * n->y,
               u->z - 2.0 * t * n->z};
  return v;
}

static inline vec3_t refract(const vec3_t *uv, const vec3_t *n, double etai_over_etat) {

  double cos_theta = fmin(-dot(uv, n), 1.0);
  vec3_t temp = mul(cos_theta, n);
  temp = add(uv, &temp);
  vec3_t r_perp = mul(etai_over_etat, &temp);
  double t = -sqrt(fabs(1.0 - dot(&r_perp, &r_perp)));
  vec3_t r_par = mul(t, n);

  vec3_t r = add(&r_perp, &r_par);

  return r;

}

// Utility functions
static inline bool near_zero(const vec3_t *u) {
  return (fabs(u->x) < 1.0e-8) && (fabs(u->y) < 1.0e-8) && (fabs(u->z) < 1.0e-8);
}

#endif // VEC3_H_
