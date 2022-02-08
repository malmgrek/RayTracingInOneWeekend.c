#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "vec3.h"

#define PI 3.1415926535897932385
#define DEG2RAD(degrees) (((degrees) * PI) / 180.0)
#define RANDOM_DOUBLE_UNIT (rand() / (RAND_MAX + 1.0))
#define RANDOM_DOUBLE(min, max) (min + (max - min) * RANDOM_DOUBLE_UNIT)

static inline double clip(double x, double min, double max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

static inline double reflectance(double cosine, double ref_idx) {
  double R0 = (1.0 - ref_idx) / (1.0 + ref_idx);
  R0 *= R0;
  return R0 + (1.0 - R0) * pow((1.0 - cosine), 5);
}

void progress_bar(double rate);

#endif // UTILS_H_
