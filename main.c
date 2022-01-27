#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"

/* Initialize progress bar */
char bar[13];

/* /\* Check if a ray originating from origin intersects a given sphere *\/ */
/* // TODO: This is to be replaced with the function sphere_hit */
/* double hit_sphere(const vec3_t center, double radius, const ray_t ray) { */
/*   vec3_t oc = sub(ray.origin, center); */
/*   double a = norm_squared(ray.direction); */
/*   double half_b = dot(oc, ray.direction); */
/*   double c = norm_squared(oc) - radius * radius; */
/*   double discr = half_b * half_b - a * c; */
/*   // If ray hits sphere, return positive root, otherwise -1.0 */
/*   return (discr < 0) ? -1.0 : (-half_b - sqrt(discr)) / a; */
/* } */

// TODO: Take hit boolean as input instead (different from C++)
color_t ray_color(const ray_t ray, bool did_hit, vec3_t normal) {
  /* vec3_t center = { 0, 0, -1 }; */
  /* double radius = 0.5; */
  /* double t = hit_sphere(center, radius, ray); */
  /* // If ray hits sphere, add shading using unit normal */
  /* if (t > 0.0) { */
  /*   vec3_t normal = unit_vector(sub(ray_at(ray, t), center)); */
  /*   color_t color = { normal.x + 1.0, normal.y + 1.0, normal.z + 1.0 }; */
  /*   return mul(0.5, color); */
  /* } */
  if (did_hit) {
    color_t color = {
      normal.x + 1.0,
      normal.y + 1.0,
      normal.z + 1.0
    };
    return mul(0.5, color);
  }
  vec3_t unit = unit_vector(ray.direction);
  double t = 0.5 * (unit.y + 1.0);
  color_t white = { 1.0, 1.0, 1.0 };
  color_t lightblue = { 0.5, 0.7, 1.0 };
  color_t color = add(mul(1.0 - t, white), mul(t, lightblue));
  return color;
}

int main() {

  color_t pixel_color;

  /* Image */
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = (int) (image_width / aspect_ratio);

  /* Camera */
  double viewport_height = 2.0;
  double viewport_width = aspect_ratio * viewport_height;
  double focal_length = 1.0;
  vec3_t focal = { 0.0, 0.0, focal_length };

  vec3_t origin = { 0.0, 0.0, 0.0 };
  vec3_t horizontal = { viewport_width, 0.0,             0.0 };
  vec3_t vertical =   { 0.0,            viewport_height, 0.0 };
  // origin - horizontal/2 - vertical/2 - focal
  vec3_t lower_left_corner = sub(sub(origin, mul(0.5, horizontal)),
                               add(mul(0.5, vertical), focal));

  // NOTE: In C++ one can use shared pointers to wrap a list of
  // hittable objects (possible different) to a list that is looped over
  // in the main loop. In C, we can't do so. Instead, we create a list
  // of structs beforehand, and loop them explicitly.

  /* const int num_spheres = 2; */
  /* sphere_t *spheres[num_spheres]; */
  /* vec3_t center0 = { 0.0, 0.0, -1.0 }; */
  /* spheres[0]->center = center0; */
  /* spheres[0]->radius = 0.5; */
  /* vec3_t center1 = { 0.0, -100.5, -1.0 }; */
  /* spheres[1]->center = center1; */
  /* spheres[1]->radius = 100.0; */

  sphere_t *sphere = calloc(1, sizeof(sphere_t));
  vec3_t center = {0.0, 0.0, -1.0};
  sphere->center = center;
  sphere->radius = 0.5;

  /* Render */
  printf("P3\n%d %d\n255\n", image_width, image_height);
  for (int j = image_height-1; j >= 0; --j) {
    for (int i = 0; i < image_width; ++i) {

      /* Progress bar ------------------------------------------------------------ */
      progress_bar(bar, 1.0 - (double) j / image_height);
      /* ------------------------------------------------------------------------- */

      double u = (double) i / (image_width - 1);
      double v = (double) j / (image_height - 1);
      // direction = lower_left_corner + u * horizontal + v * vertical - origin
      vec3_t direction = add(add(lower_left_corner, mul(u, horizontal)),
                             sub(mul(v, vertical), origin));
      ray_t ray = { origin, direction };

      for (int k = 0; k < 1; ++k) {
        bool did_hit = sphere_hit(sphere, ray, 0.0, 1000000000.0);
        pixel_color = ray_color(ray, did_hit, sphere->normal);
      }

      write_color(pixel_color);

    }
  }

  free(sphere);

}
