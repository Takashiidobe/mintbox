#include "./internal.h"
#include <mint/mintbind.h>
#include <stdio.h>

int fgetc(FILE *stream) {
  if (!stream)
    return EOF;

  if (stream->has_ungetc) {
    stream->has_ungetc = 0;
    return (int)stream->ungetc_value;
  }

  if (stream->handle < 0) {
    __stdio_set_error(stream);
    return EOF;
  }

  unsigned char ch = 0;
  long ret = Fread((short)stream->handle, 1, &ch);
  if (ret == 0) {
    __stdio_set_eof(stream);
    return EOF;
  }
  if (ret < 0) {
    __stdio_set_error(stream);
    return EOF;
  }

  return (int)ch;
}
