#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void *calloc(size_t count, size_t size) {
  if (count != 0 && size > SIZE_MAX / count) {
    return NULL;
  }

  size_t total = count * size;
  void *ptr = malloc(total);
  if (!ptr) {
    return NULL;
  }

  if (total != 0) {
    memset(ptr, 0, total);
  }

  return ptr;
}
