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

vec3_t emul(vec3_t u, vec3_t v) {
  vec3_t w = { u.x * v.x, u.y * v.y, u.z * v.z };
  return w;
}

vec3_t unit_vector(vec3_t direction) {
  double t = norm(direction);
  vec3_t v = { direction.x / t, direction.y / t, direction.z / t };
  return v;
}

vec3_t random_vector_unit() {
  vec3_t u = { random_double_unit(),
               random_double_unit(),
               random_double_unit() };
  return u;
}

vec3_t random_vector(double min, double max) {
  vec3_t u = { random_double(min, max),
               random_double(min, max),
               random_double(min, max) };
  return u;
}

vec3_t random_in_unit_sphere() {
  vec3_t p = random_vector(-1.0, 1.0);
  if (norm_squared(p) < 1.0) {
    return p;
  } else {
    return random_in_unit_sphere();
  }
}

vec3_t random_on_unit_sphere() {
  return unit_vector(random_in_unit_sphere());
}

bool near_zero(vec3_t u) {
  const double eps = 1e-8;
  return (fabs(u.x) < eps) && (fabs(u.y) < eps) && (fabs(u.z) < eps);
}

vec3_t reflect(vec3_t u, vec3_t n) {
  vec3_t v = sub(u, mul(2.0 * dot(u, n), n));
  return v;
}

vec3_t refract(vec3_t uv, vec3_t n, double etai_over_etat) {
  double cos_theta = fmin(dot(mul(-1.0, uv), n), 1.0);
  vec3_t r_out_perp = mul(etai_over_etat,
                          add(uv, mul(cos_theta, n)));
  vec3_t r_out_parallel = mul(-sqrt(fabs(1.0 - norm_squared(r_out_perp))),
                              n);
  return add(r_out_perp, r_out_parallel);
}
