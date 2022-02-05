#ifndef COLOR_H_
#define COLOR_H_

#include "ray.h"
#include "utils.h"
#include "vec3.h"

typedef vec3_t color_t;

color_t Color(double r, double g, double b);

void write_color(color_t *pixel_color, int samples_per_pixel);

#endif // COLOR_H_
