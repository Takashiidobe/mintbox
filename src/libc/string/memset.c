#include <stddef.h>

void *memset(void *dest, int c, size_t n) {
  unsigned char *d = dest;
  unsigned char value = c;

  for (size_t i = 0; i < n; i++) {
    d[i] = value;
  }
  return dest;
}
