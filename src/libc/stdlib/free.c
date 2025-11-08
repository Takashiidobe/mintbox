#include "alloc_internal.h"
#include <stdlib.h>

void free(void *ptr) {
  if (!ptr)
    return;
  ((Block *)ptr - 1)->free = 1;
}
