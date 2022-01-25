#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "utils.h"

#include <stdio.h>


// Progress bar
char bar[13];


Color ray_color(const Ray r, Color color) {
  Vec3 u;
  Color color1 = { 1.0, 1.0, 1.0 };
  Color color2 = { 0.5, 0.7, 1.0 };
  u = unit_vector(u, r.direction);
  double t = 0.5 * (u.y + 1.0);
  color = add(lmul(1.0 - t, color1), lmul(t, color2));
  return color;
}


int main() {

  // Image
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = (int) (image_width / aspect_ratio);

  // Camera
  double viewport_height = 2.0;
  double viewport_width = aspect_ratio * viewport_height;
  double focal_length = 1.0;

  Vec3 origin = { 0.0, 0.0, 0.0 };
  Vec3 horizontal = { viewport_width, 0.0,             0.0 };
  Vec3 vertical =   { 0.0,            viewport_height, 0.0 };
  Vec3 lower_left_corner = {
    origin.x - horizontal.x / 2.0 - vertical.x / 2.0 - 0.0,
    origin.y - horizontal.y / 2.0 - vertical.y / 2.0 - 0.0,
    origin.z - horizontal.z / 2.0 - vertical.z / 2.0 - focal_length,
  };

  // Render
  printf("P3\n%d %d\n255\n", image_width, image_height);
  for (int j = image_height-1; j >= 0; --j) {
    for (int i = 0; i < image_width; ++i) {

      // Progress bar ------------------------------------------------------------
      fprintf(stderr, "\r%s", progress_bar(bar, 1.0 - (double) j / image_height));
      fflush(stdout);
      // -------------------------------------------------------------------------

      double u = (double) i / (image_width - 1);
      double v = (double) j / (image_height - 1);
      Vec3 direction = {
        lower_left_corner.x + u * horizontal.x + v * vertical.x - origin.x,
        lower_left_corner.y + u * horizontal.y + v * vertical.y - origin.y,
        lower_left_corner.z + u * horizontal.z + v * vertical.z - origin.z
      };
      Ray r = { origin, direction };
      Color pixel_color; pixel_color = ray_color(r, pixel_color);

      write_color(pixel_color);

    }
  }

}
