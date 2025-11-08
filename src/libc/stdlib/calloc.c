#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void *calloc(size_t nmemb, size_t size) {
  if (size && nmemb > SIZE_MAX / size)
    return NULL; /* overflow */
  size_t total = nmemb * size;

  void *p = malloc(total);
  if (!p)
    return NULL;

  memset(p, 0, total);
  return p;
}
