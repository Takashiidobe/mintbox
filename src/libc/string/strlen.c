#include <stddef.h>

size_t strlen(const char *s) {
  const char *p = s;
  for (; *s; s++)
    ;
  return s - p;
}
