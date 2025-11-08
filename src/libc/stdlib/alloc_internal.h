#ifndef CBOX_ALLOC_INTERNAL_H
#define CBOX_ALLOC_INTERNAL_H

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

/* Internal block header used by all allocator TUs */
typedef struct Block {
  long size;          /* payload size (bytes) */
  int free;           /* 1 = free, 0 = used   */
  struct Block *next; /* singly-linked list   */
} Block;

/* The global head of the block list (defined in alloc_core.c). */
extern Block *__alloc_head;

/* Core helpers (defined in alloc_core.c). */
size_t __alloc_align_up(size_t size);
void __alloc_append_block(Block *b);

#endif /* CBOX_ALLOC_INTERNAL_H */
