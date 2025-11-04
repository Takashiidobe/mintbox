#include "./gemdos/file.h"
#include <stdio.h>

int remove(const char *path) {
  long ret = Fdelete(path);
  return ret < 0 ? -1 : 0;
}
