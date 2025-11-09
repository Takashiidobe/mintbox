#include "./internal.h"
#include <stdio.h>

int ferror(FILE *f) {
  if (!f)
    return 1;
  return (f->state & FILE_STATE_ERR) != 0;
}
