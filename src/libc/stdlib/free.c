#include "../gemdos/memory.h"
#include <stdlib.h>

void free(void *ptr) {
  if (!ptr) {
    return;
  }

  unsigned char *raw = ptr - sizeof(size_t);
  Mfree(raw);
}
