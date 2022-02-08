#ifndef COLOR_H_
#define COLOR_H_

#include "ray.h"
#include "utils.h"
#include "vec3.h"

typedef vec3_t color_t;

static inline color_t Color(double r, double g, double b) {
  color_t color = { r, g, b };
  return color;
}

static inline void write_color(const color_t *pixel_color, int samples_per_pixel) {
  // Divide the color by the number of samples
  printf("%d %d %d\n",
         (int) (256 * clip(sqrt(pixel_color->x / samples_per_pixel), 0.0, 0.999)),
         (int) (256 * clip(sqrt(pixel_color->y / samples_per_pixel), 0.0, 0.999)),
         (int) (256 * clip(sqrt(pixel_color->z / samples_per_pixel), 0.0, 0.999)));
}

#endif // COLOR_H_
