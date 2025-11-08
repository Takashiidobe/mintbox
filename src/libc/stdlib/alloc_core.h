#include "alloc_internal.h"

Block *__alloc_head = NULL;

size_t __alloc_align_up(size_t size) {
  const size_t align = sizeof(long);
  const size_t mask = align - 1;
  if (size > SIZE_MAX - mask)
    return 0;
  return (size + mask) & ~mask;
}

void __alloc_append_block(Block *b) {
  if (!__alloc_head) {
    __alloc_head = b;
    return;
  }
  Block *tail = __alloc_head;
  while (tail->next)
    tail = tail->next;
  tail->next = b;
}
