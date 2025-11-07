#include <stddef.h>

int strncmp(const char *s1, const char *s2, size_t n) {
  const unsigned char *l = (void *)s1;
  const unsigned char *r = (void *)s2;
  if (!n--)
    return 0;
  for (; *l && *r && n && *l == *r; l++, r++, n--)
    ;
  return *l - *r;
}
