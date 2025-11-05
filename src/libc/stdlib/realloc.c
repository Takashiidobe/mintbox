#include "../gemdos/memory.h"
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HEADER_SIZE sizeof(size_t)

void *realloc(void *ptr, size_t size) {
  if (!ptr) {
    return malloc(size);
  }

  if (size == 0) {
    free(ptr);
    return NULL;
  }

  unsigned char *raw = (unsigned char *)ptr - HEADER_SIZE;
  size_t old_size = *(size_t *)raw;

  if (size > SIZE_MAX - HEADER_SIZE) {
    return NULL;
  }

  size_t total = size + HEADER_SIZE;
  if (total > (size_t)INT32_MAX) {
    return NULL;
  }

  int32_t res = Mshrink(raw, (int32_t)total);
  if (res >= 0) {
    *(size_t *)raw = size;
    return ptr;
  }

  void *new_ptr = malloc(size);
  if (!new_ptr) {
    return NULL;
  }

  size_t copy_size = old_size < size ? old_size : size;
  memcpy(new_ptr, ptr, copy_size);
  free(ptr);
  return new_ptr;
}
