#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void *memalign(size_t alignment, size_t size) {
  if (alignment < sizeof(void *))
    alignment = sizeof(void *);
  if ((alignment & (alignment - 1)) != 0) { // must be power of two
    errno = EINVAL;
    return NULL;
  }

  // We need space for alignment slack + 1 word to store the original pointer.
  size_t total = size + alignment - 1 + sizeof(void *);
  void *raw = malloc(total);
  if (!raw) {
    errno = ENOMEM;
    return NULL;
  }

  // Advance past the header space, then align.
  uintptr_t start = (uintptr_t)raw + sizeof(void *);
  uintptr_t aligned = (start + (alignment - 1)) & ~(uintptr_t)(alignment - 1);

  // Stash the original pointer in the preceding word.
  ((void **)aligned)[-1] = raw;

  return (void *)aligned;
}
