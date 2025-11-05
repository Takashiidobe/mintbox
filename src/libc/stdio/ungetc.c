#include "./internal.h"
#include <stdio.h>

int ungetc(int c, FILE *stream) {
  if (!stream || c == EOF)
    return EOF;

  if (stream->has_ungetc)
    return EOF;

  stream->ungetc_value = (unsigned char)c;
  stream->has_ungetc = 1;
  return stream->ungetc_value;
}
