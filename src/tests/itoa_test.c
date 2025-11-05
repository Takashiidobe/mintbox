#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char buf[12];
  char *end = itoa(buf, INT32_MIN);

  puts(buf);
  assert(end == buf + 11);
  assert(strcmp(buf, "-2147483648") == 0);
  return 0;
}
