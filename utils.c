#include "utils.h"
#include "vec3.h"

void progress_bar(char *bar, double rate) {
  bar[0] = '[';
  bar[11] = ']';
  for (int i = 1; i <= 10; i++) {
    bar[i] = (double) i / 10.0 <= rate ? '=' : ' ';
  }
  fprintf(stderr, "\r%s", bar);
  fflush(stdout);
}

double degrees_to_radians(double degrees) {
  return degrees * PI / 180.0;
}

double random_double_unit() {
  return rand() / (RAND_MAX + 1.0);
}

double random_double(double min, double max) {
  return min + (max - min) * random_double_unit();
}

double clamp(double x, double min, double max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

const double PI = 3.1415926535897932385;
