#include "alloc_internal.h"
#include <stdlib.h>
#include <string.h>

void *realloc(void *ptr, size_t new_size) {
  if (!ptr)
    return malloc(new_size);
  if (new_size == 0) {
    free(ptr);
    return NULL;
  }

  Block *b = (Block *)ptr - 1;
  size_t old = (size_t)b->size;

  void *p = malloc(new_size);
  if (!p)
    return NULL;

  size_t n = old < new_size ? old : new_size;
  if (n)
    memcpy(p, ptr, n);
  free(ptr);
  return p;
}
