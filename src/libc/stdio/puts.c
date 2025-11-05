#include <stdio.h>

int puts(const char *s) {
  const char *p = s;

  while (*p) {
    putchar(*p++);
  }
  putchar('\r');
  putchar('\n');

  return 0;
}
