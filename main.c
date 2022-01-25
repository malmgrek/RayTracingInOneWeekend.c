#include "color.h"
#include "vec3.h"

#include <stdio.h>


char *progress_bar(char *bar, double rate) {
  bar[0] = '[';
  bar[11] = ']';
  for (int i = 1; i <= 10; i++) {
    bar[i] = (double) i / 10.0 <= rate ? '=' : ' ';
  }
  return bar;
}


int main() {

  char bar[13];

  // Image
  const int image_width = 256;
  const int image_height = 256;

  // Render
  printf("P3\n%d %d\n255\n", image_width, image_height);
  for (int j = image_height-1; j >= 0; --j) {
    for (int i = 0; i < image_width; ++i) {

      fprintf(stderr, "\r%s", progress_bar(bar, 1.0 - (double) j / image_height));
      fflush(stdout);

      Color pixel_color = {
        (double) i / (image_width - 1),
        (double) j / (image_height - 1),
        0.25
      };

      write_color(pixel_color);

    }
  }

}
