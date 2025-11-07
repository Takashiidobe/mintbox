#include <stdio.h>
#include <string.h>

int puts(const char *s) {
  size_t len = strlen(s);
  if (len && fwrite(s, 1, len, stdout) != len)
    return EOF;
  if (fputc('\n', stdout) == EOF)
    return EOF;
  return 1;
}
