#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>

void progress_bar(char *bar, double rate);
double degrees_to_radians(double degrees);
double random_double();
double clamp(double x, double min, double max);

extern const double PI;

#endif // UTILS_H_
