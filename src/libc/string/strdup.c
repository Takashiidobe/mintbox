#include <stdlib.h>
#include <string.h>

char *strdup(const char *s) {
  size_t len = strlen(s) + 1;
  char *copy = malloc(len);

  if (!copy) {
    return NULL;
  }
  memcpy(copy, s, len);
  return copy;
}
