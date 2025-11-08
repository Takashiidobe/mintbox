#include <stdlib.h>

void *bsearch(const void *key, const void *base, size_t nmemb, size_t size,
              int (*compar)(const void *, const void *)) {
  if (!key || !base || size == 0 || !compar)
    return NULL;

  const char *b = (const char *)base;

  while (nmemb) {
    size_t mid = nmemb / 2;
    const char *elem = b + mid * size;
    int cmp = compar(key, elem);

    if (cmp > 0) {
      b = elem + size;
      nmemb -= mid + 1;
    } else if (cmp < 0) {
      nmemb = mid;
    } else {
      return (void *)elem;
    }
  }

  return NULL;
}
