#include "./gemdos/memory.h"
#include <stdlib.h>

#define HEADER_SIZE sizeof(size_t)

void free(void *ptr) {
  if (!ptr) {
    return;
  }

  unsigned char *raw = (unsigned char *)ptr - HEADER_SIZE;
  (void)Mfree(raw);
}
