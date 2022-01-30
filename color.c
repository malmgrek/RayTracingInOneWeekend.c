#include "color.h"

void write_color(color_t pixel_color, int samples_per_pixel) {
  double r = pixel_color.x;
  double g = pixel_color.y;
  double b = pixel_color.z;

  // Divide the color by the number of samples
  double scale = 1.0 / (double) samples_per_pixel;
  r *= scale;
  g *= scale;
  b *= scale;

  printf("%d %d %d\n",
         (int) (255.999 * clamp(r, 0.0, 0.999)),
         (int) (255.999 * clamp(g, 0.0, 0.999)),
         (int) (255.999 * clamp(b, 0.0, 0.999)));
}
