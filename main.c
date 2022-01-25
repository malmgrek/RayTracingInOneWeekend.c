#include <stdio.h>


char *progress_bar(char *bar, double rate) {
  bar[0] = '[';
  for (int i = 1; i <= 10; i++) {
    if ((double) i / 10.0 <= rate) {
      bar[i] = '=';
    } else {
      bar[i] = ' ';
    }
  }
  bar[11] = ']';
  return bar;
}


int main() {

  char bar[12];

  // Image
  const int image_width = 256;
  const int image_height = 256;

  // Render
  printf("P3\n%d %d\n255\n", image_width, image_height);
  for (int j = image_height-1; j >= 0; --j) {
    for (int i = 0; i < image_width; ++i) {

      fprintf(stderr, "\r%s", progress_bar(bar, 1.0 - (double) j / image_height));
      fflush(stdout);

      double r = (double) i / (image_width - 1);
      double g = (double) j / (image_height - 1);
      double b = 0.25;

      int ir = (int) (255.999 * r);
      int ib = (int) (255.999 * b);
      int ig = (int) (255.999 * g);

      printf("%d %d %d\n", ir, ig, ib);
    }
  }

}
