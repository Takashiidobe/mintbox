#include <stdio.h>

int fputc(int c, FILE *f) {
  unsigned char ch = c;
  if (fwrite(&ch, 1, 1, f) != 1)
    return EOF;
  return ch;
}
