#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Block {
  long size;   // allocation size tracked in machine word units
  int free;    // free = 1, used = 0
  struct Block *next;
} Block;

static Block *head = NULL;

static size_t align_up(size_t size) {
  size_t align = sizeof(long);
  size_t mask = align - 1;
  if (size > SIZE_MAX - mask) {
    return 0;
  }
  return (size + mask) & ~mask;
}

static void append_block(Block *block) {
  if (!head) {
    head = block;
    return;
  }

  Block *tail = head;
  while (tail->next) {
    tail = tail->next;
  }
  tail->next = block;
}

static void *tiny_malloc(size_t size) {
  if (size == 0) {
    size = 1;
  }

  size = align_up(size);
  if (size == 0 || size > (size_t)LONG_MAX) {
    return NULL;
  }

  for (Block *b = head; b; b = b->next) {
    if (b->free && (size_t)b->size >= size) {
      b->free = 0;
      return b + 1;
    }
  }

  size_t total = sizeof(Block) + size;
  if (total > (size_t)LONG_MAX) {
    return NULL;
  }

  Block *b = (Block *)sbrk((intptr_t)total);
  if (b == (void *)-1) {
    return NULL;
  }

  b->size = (long)size;
  b->free = 0;
  b->next = NULL;
  append_block(b);
  return b + 1;
}

static void tiny_free(void *ptr) {
  if (!ptr) {
    return;
  }

  ((Block *)ptr - 1)->free = 1;
}

static void *tiny_realloc(void *ptr, size_t new_size) {
  if (!ptr) {
    return tiny_malloc(new_size);
  }

  if (new_size == 0) {
    tiny_free(ptr);
    return NULL;
  }

  Block *b = (Block *)ptr - 1;
  size_t old = (size_t)b->size;

  void *p = tiny_malloc(new_size);
  if (!p) {
    return NULL;
  }

  size_t n = old < new_size ? old : new_size;
  memcpy(p, ptr, n);
  tiny_free(ptr);
  return p;
}

static void *tiny_calloc(size_t nmemb, size_t size) {
  if (size && nmemb > SIZE_MAX / size) {
    return NULL;
  }

  size_t total = nmemb * size;
  void *p = tiny_malloc(total);
  if (!p) {
    return NULL;
  }

  memset(p, 0, total);
  return p;
}

void *malloc(size_t size) {
  return tiny_malloc(size);
}

void free(void *ptr) {
  tiny_free(ptr);
}

void *realloc(void *ptr, size_t size) {
  return tiny_realloc(ptr, size);
}

void *calloc(size_t nmemb, size_t size) {
  return tiny_calloc(nmemb, size);
}
