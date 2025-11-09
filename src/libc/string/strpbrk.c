#include <stddef.h>

static int in_set(char ch, const char *set) {
  while (*set) {
    if (*set++ == ch) {
      return 1;
    }
  }
  return 0;
}

char *strpbrk(const char *s, const char *accept) {
  while (*s) {
    if (in_set(*s, accept)) {
      return (char *)s;
    }
    s++;
  }
  return NULL;
}
