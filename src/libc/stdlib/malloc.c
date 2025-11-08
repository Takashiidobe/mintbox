#include "alloc_core.h"
#include "alloc_internal.h"
#include <stdlib.h>
#include <unistd.h>

void *malloc(size_t size) {
  if (size == 0)
    size = 1;

  size = __alloc_align_up(size);
  if (size == 0 || size > (size_t)LONG_MAX)
    return NULL;

  for (Block *b = __alloc_head; b; b = b->next) {
    if (b->free && (size_t)b->size >= size) {
      b->free = 0;
      return (void *)(b + 1);
    }
  }

  size_t total = sizeof(Block) + size;
  if (total > (size_t)LONG_MAX)
    return NULL;

  Block *b = (Block *)sbrk((intptr_t)total);
  if (b == (void *)-1)
    return NULL;

  b->size = (long)size;
  b->free = 0;
  b->next = NULL;
  __alloc_append_block(b);

  return (void *)(b + 1);
}
