#include <stdio.h>

long Fdelete(const char *path);

int remove(const char *path) {
  long ret = Fdelete(path);
  return ret < 0 ? -1 : 0;
}
