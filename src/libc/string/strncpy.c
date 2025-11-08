#include <stddef.h>

char *strncpy(char *dest, const char *src, size_t n) {
  char *d = dest;
  size_t i = 0;

  for (; i < n && src[i]; i++) {
    d[i] = src[i];
  }
  for (; i < n; i++) {
    d[i] = '\0';
  }
  return dest;
}
