#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void progress_bar(double rate);
double degrees_to_radians(double degrees);
double random_double_unit();
double random_double(double min, double max);
double clip(double x, double min, double max);
double reflectance(double cosine, double ref_idx);

extern const double PI;

#endif // UTILS_H_
