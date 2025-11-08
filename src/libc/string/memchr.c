#include <stddef.h>

void *memchr(const void *s, int c, size_t n) {
  const unsigned char *src = s;
  unsigned char ch = (unsigned char)c;

  while (n--) {
    if (*src == ch) {
      return (void *)src;
    }
    src++;
  }
  return NULL;
}
