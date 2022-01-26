#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "utils.h"

#include <stdio.h>
#include <stdbool.h>

/* Initialize progress bar */
char bar[13];

/* Check if a ray originating from origin intersects a given sphere */
double hit_sphere(const vec3_t center, double radius, const ray_t r) {
  vec3_t oc = sub(r.origin, center);
  double a = norm_squared(r.direction);
  double half_b = dot(oc, r.direction);
  double c = norm_squared(oc) - radius * radius;
  double discr = half_b * half_b - a * c;
  // If ray hits sphere, return positive root, otherwise -1.0
  return (discr < 0) ? -1.0 : (-half_b - sqrt(discr)) / a;
}

color_t ray_color(const ray_t r) {
  vec3_t center = { 0, 0, -1 };
  double radius = 0.5;
  double t = hit_sphere(center, radius, r);
  // If ray hits sphere, add shading using unit normal
  if (t > 0.0) {
    vec3_t normal = unit_vector(sub(ray_at(r, t), center));
    color_t color = { normal.x + 1.0, normal.y + 1.0, normal.z + 1.0 };
    return mul(0.5, color);
  }
  vec3_t unit = unit_vector(r.direction);
  t = 0.5 * (unit.y + 1.0);
  color_t white = { 1.0, 1.0, 1.0 };
  color_t lightblue = { 0.5, 0.7, 1.0 };
  color_t color = add(mul(1.0 - t, white), mul(t, lightblue));
  return color;
}

int main() {

  color_t pixel_color;

  /* Image */
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 800;
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

  /* Render */
  printf("P3\n%d %d\n255\n", image_width, image_height);
  for (int j = image_height-1; j >= 0; --j) {
    for (int i = 0; i < image_width; ++i) {

      /* Progress bar ------------------------------------------------------------ */
      fprintf(stderr, "\r%s", progress_bar(bar, 1.0 - (double) j / image_height));
      fflush(stdout);
      /* ------------------------------------------------------------------------- */

      double u = (double) i / (image_width - 1);
      double v = (double) j / (image_height - 1);
      vec3_t direction = {
        lower_left_corner.x + u * horizontal.x + v * vertical.x - origin.x,
        lower_left_corner.y + u * horizontal.y + v * vertical.y - origin.y,
        lower_left_corner.z + u * horizontal.z + v * vertical.z - origin.z
      };
      ray_t r = { origin, direction };
      pixel_color = ray_color(r);

      write_color(pixel_color);

    }
  }

}
