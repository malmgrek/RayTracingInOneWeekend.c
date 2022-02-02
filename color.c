#include "color.h"

const color_t black = { 0.0, 0.0, 0.0 };
const color_t white = { 1.0, 1.0, 1.0 };
const color_t lightblue = { 0.5, 0.7, 1.0 };

color_t Color(double r, double g, double b) {
  color_t color = { r, g, b };
  return color;
}

void write_color(color_t *pixel_color, int samples_per_pixel) {

  // Divide the color by the number of samples
  double scale = 1.0 / samples_per_pixel;
  printf("%d %d %d\n",
         (int) (256 * clip(sqrt(scale * pixel_color->x), 0.0, 0.999)),
         (int) (256 * clip(sqrt(scale * pixel_color->y), 0.0, 0.999)),
         (int) (256 * clip(sqrt(scale * pixel_color->z), 0.0, 0.999)));
}
