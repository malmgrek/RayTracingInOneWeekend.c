#include "vec3.h"

vec3_t Vector(double x, double y, double z) {
  vec3_t u = { x, y, z };
  return u;
}

vec3_t Point(double x, double y, double z) {
  vec3_t u = { x, y, z };
  return u;
}

double dot(vec3_t *u, vec3_t *v) {
  return u->x * v->x + u->y * v->y + u->z * v->z;
}

vec3_t mul(double t, vec3_t *u) {
  vec3_t v = { t * u->x, t * u->y, t * u->z };
  return v;
}

vec3_t add(vec3_t *u, vec3_t *v) {
  vec3_t w = { u->x + v->x, u->y + v->y, u->z + v->z };
  return w;
}

vec3_t sub(vec3_t *u, vec3_t *v) {
  vec3_t w = { u->x - v->x, u->y - v->y, u->z - v->z };
  return w;
}

vec3_t cross(vec3_t *u, vec3_t *v) {
  vec3_t w = { u->y * v->z - u->z * v->y,
               u->z * v->x - u->x * v->z,
               u->x * v->y - u->y * v->x };
  return w;
}

double norm(vec3_t *u) {
  double t = sqrt(dot(u, u));
  return t;
}

vec3_t emul(vec3_t *u, vec3_t *v) {
  vec3_t w = { u->x * v->x, u->y * v->y, u->z * v->z };
  return w;
}

vec3_t unit_vector(vec3_t *direction) {
  // double t = norm(*direction);
  double t = sqrt(direction->x * direction->x +
                  direction->y * direction->y +
                  direction->z * direction->z);
  vec3_t v = { direction->x / t, direction->y / t, direction->z / t };
  return v;
}

vec3_t random_vector_unit() {
  vec3_t u = { RANDOM_DOUBLE_UNIT,
               RANDOM_DOUBLE_UNIT,
               RANDOM_DOUBLE_UNIT };
  return u;
}

vec3_t random_vector(double min, double max) {
  vec3_t u = { RANDOM_DOUBLE(min, max),
               RANDOM_DOUBLE(min, max),
               RANDOM_DOUBLE(min, max) };
  return u;
}

vec3_t random_in_unit_disk() {
  vec3_t p = { RANDOM_DOUBLE(-1.0, 1.0), RANDOM_DOUBLE(-1.0, 1.0), 0.0 };
  if (dot(&p, &p) < 1.0) {
    return p;
  } else {
    return random_in_unit_disk();
  }
}

vec3_t random_in_unit_sphere() {
  vec3_t p = random_vector(-1.0, 1.0);
  if (dot(&p, &p) < 1.0) {
    return p;
  } else {
    return random_in_unit_sphere();
  }
}

vec3_t random_on_unit_sphere() {
  vec3_t tmp = random_in_unit_sphere();
  return unit_vector(&tmp);
}

bool near_zero(vec3_t *u) {
  return (fabs(u->x) < 1.0e-8) && (fabs(u->y) < 1.0e-8) && (fabs(u->z) < 1.0e-8);
}

vec3_t reflect(vec3_t *u, vec3_t *n) {
  double t = dot(u, n);
  // vec3_t v = u - 2.0 * (u.n)n
  vec3_t v = {u->x - 2.0 * t * n->x,
               u->y - 2.0 * t * n->y,
               u->z - 2.0 * t * n->z};
  return v;
}

vec3_t refract(vec3_t *uv, vec3_t *n, double etai_over_etat) {

  /* cos_theta = min(-uv.n, 1.0) */
  double cos_theta = fmin(-1.0 * (uv->x * n->x + uv->y * n->y + uv->z * n->z),
                          1.0);

  /* r_out_perp = etai_over_etat * (uv + cos_theta * n) */
  double r_perp_x = etai_over_etat * (uv->x + cos_theta * n->x);
  double r_perp_y = etai_over_etat * (uv->y + cos_theta * n->y);
  double r_perp_z = etai_over_etat * (uv->z + cos_theta * n->z);

  double t = -sqrt(fabs(1.0
                        - r_perp_x * r_perp_x
                        - r_perp_y * r_perp_y
                        - r_perp_z * r_perp_z));
  double r_par_x = t * n->x;
  double r_par_y = t * n->y;
  double r_par_z = t * n->z;

  vec3_t r = { r_perp_x + r_par_x, r_perp_y + r_par_y, r_perp_z + r_par_z };

  return r;

}
