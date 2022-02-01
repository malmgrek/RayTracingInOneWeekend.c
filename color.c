#include "color.h"

const color_t black = { 0.0, 0.0, 0.0 };
const color_t white = { 1.0, 1.0, 1.0 };
const color_t lightblue = { 0.5, 0.7, 1.0 };

color_t Color(double red, double green, double blue) {
  color_t color = { red, green, blue };
  return color;
}

void write_color(color_t pixel_color, int samples_per_pixel) {
  double r = pixel_color.x;
  double g = pixel_color.y;
  double b = pixel_color.z;

  // Divide the color by the number of samples
  double scale = 1.0 / samples_per_pixel;
  r = sqrt(scale * r);
  g = sqrt(scale * g);
  b = sqrt(scale * b);

  printf("%d %d %d\n",
         (int) (256 * clamp(r, 0.0, 0.999)),
         (int) (256 * clamp(g, 0.0, 0.999)),
         (int) (256 * clamp(b, 0.0, 0.999)));
}
