#include <stdlib.h>

int atoi(const char *s) {
  int n = 0, neg = 0;
  while (*s == ' ')
    s++;
  switch (*s) {
  case '-':
    neg = 1;
  case '+':
    s++;
  }
  while (*s >= '0' && *s <= '9')
    n = 10 * n - (*s++ - '0');
  return neg ? n : -n;
}
