#include "utils.h"

char *progress_bar(char *bar, double rate) {
  bar[0] = '[';
  bar[11] = ']';
  for (int i = 1; i <= 10; i++) {
    bar[i] = (double) i / 10.0 <= rate ? '=' : ' ';
  }
  return bar;
}
