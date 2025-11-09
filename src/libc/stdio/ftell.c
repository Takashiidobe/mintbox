#include "./internal.h"
#include <mint/mintbind.h>
#include <stdio.h>
#include <unistd.h>

long ftell(FILE *stream) {
  if (!stream)
    return -1;

  if (stream->handle < 0) {
    __stdio_set_error(stream);
    return -1;
  }

  long result = Fseek(0, (short)stream->handle, SEEK_CUR);
  if (result < 0) {
    __stdio_set_error(stream);
    return -1;
  }

  return result;
}
