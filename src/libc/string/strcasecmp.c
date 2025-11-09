#include <stddef.h>

static unsigned char tolower_ascii(unsigned char ch) {
  if (ch >= 'A' && ch <= 'Z') {
    return (unsigned char)(ch - 'A' + 'a');
  }
  return ch;
}

int strcasecmp(const char *s1, const char *s2) {
  while (*s1 && tolower_ascii((unsigned char)*s1) ==
                   tolower_ascii((unsigned char)*s2)) {
    s1++;
    s2++;
  }
  return (int)tolower_ascii((unsigned char)*s1) -
         (int)tolower_ascii((unsigned char)*s2);
}

int strncasecmp(const char *s1, const char *s2, size_t n) {
  if (n == 0) {
    return 0;
  }
  while (--n && *s1 && tolower_ascii((unsigned char)*s1) ==
                      tolower_ascii((unsigned char)*s2)) {
    s1++;
    s2++;
  }
  return (int)tolower_ascii((unsigned char)*s1) -
         (int)tolower_ascii((unsigned char)*s2);
}
