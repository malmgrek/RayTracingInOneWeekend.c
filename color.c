#include "color.h"

void write_color(Color pixel_color) {
  printf("%d %d %d\n",
         (int) (255.999 * pixel_color.x),
         (int) (255.999 * pixel_color.y),
         (int) (255.999 * pixel_color.z));
}
