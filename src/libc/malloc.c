#include "./gemdos/memory.h"
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

#define HEADER_SIZE sizeof(size_t)

void *malloc(size_t size) {
  size_t requested = size;
  size_t alloc_size = requested ? requested : 1;

  if (alloc_size > SIZE_MAX - HEADER_SIZE) {
    return NULL;
  }

  size_t total = alloc_size + HEADER_SIZE;
  if (total > (size_t)INT32_MAX) {
    return NULL;
  }

  void *raw = Malloc((int32_t)total);
  if ((intptr_t)raw < 0) {
    return NULL;
  }

  *(size_t *)raw = requested;
  return (unsigned char *)raw + HEADER_SIZE;
}
