#include "../gemdos/file.h"
#include "./internal.h"
#include <stdio.h>

int fgetc(FILE *stream) {
  if (!stream)
    return EOF;

  if (stream->has_ungetc) {
    stream->has_ungetc = 0;
    return (int)stream->ungetc_value;
  }

  if (stream->handle < 0)
    return EOF;

  unsigned char ch = 0;
  long ret = Fread((short)stream->handle, 1, &ch);
  if (ret <= 0)
    return EOF;

  return (int)ch;
}
