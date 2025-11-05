#include "../stdio/internal.h"
#include <stdio.h>

int ferror(FILE *f) {
  int ret = !!(f->flags);
  return ret;
}
