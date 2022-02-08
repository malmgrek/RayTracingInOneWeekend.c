#include "utils.h"

void progress_bar(double rate) {
  char bar[13];
  bar[0] = '[';
  bar[11] = ']';
  for (int i = 1; i <= 10; i++) {
    bar[i] = (double) i / 10.0 <= rate ? '=' : ' ';
  }
  fprintf(stderr, "\r%s", bar);
  fflush(stdout);
}
