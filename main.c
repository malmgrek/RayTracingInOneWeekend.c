#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "utils.h"

#include <stdio.h>
#include <stdbool.h>

/* Progress bar */
char bar[13];

bool hit_sphere(const Point3 center, double radius, const Ray r) {
  Vec3 oc = sub(r.origin, center);
  double a = dot(r.direction, r.direction);
  double b = 2.0 * dot(oc, r.direction);
  double c = dot(oc, oc) - radius * radius;
  double discriminant = b * b - 4 * a * c;
  return (discriminant > 0);
}

Color ray_color(const Ray r) {
  Vec3 center = { 0, 0, -1 };
  double radius = 0.5;
  if (hit_sphere(center, radius, r)) {
    Color color = { 1.0, 0.0, 0.0 };
    return color;
  }
  Vec3 u = unit_vector(r.direction);
  double t = 0.5 * (u.y + 1.0);
  Color white = { 1.0, 1.0, 1.0 };
  Color lightblue = { 0.5, 0.7, 1.0 };
  Color color = add(mul(1.0 - t, white), mul(t, lightblue));
  return color;
}

int main() {

  Color pixel_color;

  /* Image */
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = (int) (image_width / aspect_ratio);

  /* Camera */
  double viewport_height = 2.0;
  double viewport_width = aspect_ratio * viewport_height;
  double focal_length = 1.0;
  Vec3 focal = { 0.0, 0.0, focal_length };

  Vec3 origin = { 0.0, 0.0, 0.0 };
  Vec3 horizontal = { viewport_width, 0.0,             0.0 };
  Vec3 vertical =   { 0.0,            viewport_height, 0.0 };
  // origin - horizontal/2 - vertical/2 - focal
  Vec3 lower_left_corner = sub(sub(origin, mul(0.5, horizontal)),
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
      Vec3 direction = {
        lower_left_corner.x + u * horizontal.x + v * vertical.x - origin.x,
        lower_left_corner.y + u * horizontal.y + v * vertical.y - origin.y,
        lower_left_corner.z + u * horizontal.z + v * vertical.z - origin.z
      };
      Ray r = { origin, direction };
      pixel_color = ray_color(r);

      write_color(pixel_color);

    }
  }

}
