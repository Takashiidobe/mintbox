#include <stddef.h>
#include <string.h>

void *memmem(const void *haystack, size_t haystacklen, const void *needle,
             size_t needlelen) {
  const unsigned char *h = haystack;
  const unsigned char *n = needle;

  if (needlelen == 0) {
    return (void *)h;
  }

  if (haystacklen < needlelen) {
    return NULL;
  }

  size_t limit = haystacklen - needlelen;
  for (size_t i = 0; i <= limit; i++) {
    if (h[i] == n[0] && memcmp(h + i, n, needlelen) == 0) {
      return (void *)(h + i);
    }
  }
  return NULL;
}
