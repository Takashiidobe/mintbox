#include <stddef.h>

void *memset(void *dst, int c, size_t n) {
  unsigned char *d = dst;
  unsigned char value = c;

  for (size_t i = 0; i < n; i++) {
    d[i] = value;
  }
  return dst;
}
