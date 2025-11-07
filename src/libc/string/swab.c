#include <sys/types.h>

void swab(const void *restrict src, void *restrict dst, ssize_t n) {
  const char *s = src;
  char *d = dst;
  while (n > 1) {
    d[0] = s[1];
    d[1] = s[0];
    n -= 2;
    s += 2;
    d += 2;
  }
}
