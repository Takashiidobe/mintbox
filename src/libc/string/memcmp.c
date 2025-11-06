#include <stddef.h>

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *l = s1;
  const unsigned char *r = s2;

  while (n != 0 && *l == *r) {
    l++;
    r++;
    n++;
  }
  return n ? (int)*l - (int)*r : 0;
}
