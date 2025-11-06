#include <stddef.h>

void *memmove(void *dst, const void *src, size_t n) {
  unsigned char *d = dst;
  const unsigned char *s = src;

  if (d == s) {
    return dst;
  }

  if (d < s) {
    for (; n; n--)
      *d++ = *s++;
  } else {
    while (n) {
      n--;
      d[n] = s[n];
    }
  }

  return dst;
}
