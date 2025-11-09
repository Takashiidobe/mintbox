#include <stddef.h>

static int in_set(char ch, const char *set) {
  while (*set) {
    if (*set++ == ch) {
      return 1;
    }
  }
  return 0;
}

size_t strcspn(const char *s, const char *reject) {
  size_t count = 0;
  while (s[count]) {
    if (in_set(s[count], reject)) {
      break;
    }
    count++;
  }
  return count;
}
