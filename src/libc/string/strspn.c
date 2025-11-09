#include <stddef.h>

static int in_set(char ch, const char *set) {
  while (*set) {
    if (*set++ == ch) {
      return 1;
    }
  }
  return 0;
}

size_t strspn(const char *s, const char *accept) {
  size_t count = 0;
  while (s[count] && in_set(s[count], accept)) {
    count++;
  }
  return count;
}
