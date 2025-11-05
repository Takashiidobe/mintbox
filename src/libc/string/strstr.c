#include <string.h>

char *strstr(const char *haystack, const char *needle) {
  if (!*needle) {
    return (char *)haystack;
  }

  size_t needle_len = strlen(needle);
  if (needle_len == 0) {
    return (char *)haystack;
  }

  for (const char *h = haystack; *h; h++) {
    if (*h != *needle) {
      continue;
    }

    size_t i = 0;
    while (i < needle_len && h[i] == needle[i]) {
      i++;
    }

    if (i == needle_len) {
      return (char *)h;
    }
  }

  return NULL;
}
