#include <stddef.h>

char *strrchr(const char *s, int c) {
  const char *last = NULL;
  char ch = (char)c;

  while (*s) {
    if (*s == ch) {
      last = s;
    }
    s++;
  }
  if (ch == '\0') {
    return (char *)s;
  }
  return (char *)last;
}
