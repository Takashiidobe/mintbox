#include <string.h>

char *strtok_r(char *s, const char *delim, char **saveptr) {
  char *str = s ? s : *saveptr;
  if (str == NULL) {
    return NULL;
  }

  str += strspn(str, delim);
  if (*str == '\0') {
    *saveptr = NULL;
    return NULL;
  }

  char *end = str + strcspn(str, delim);
  if (*end == '\0') {
    *saveptr = NULL;
    return str;
  }

  *end = '\0';
  *saveptr = end + 1;
  return str;
}

char *strtok(char *s, const char *delim) {
  static char *save;
  return strtok_r(s, delim, &save);
}
