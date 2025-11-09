#include "./internal.h"
#include <mint/mintbind.h>
#include <stdio.h>

int fseek(FILE *stream, long offset, int whence) {
  if (!stream)
    return -1;

  if (stream->handle < 0) {
    __stdio_set_error(stream);
    return -1;
  }

  long result = Fseek(offset, (short)stream->handle, (short)whence);
  if (result < 0) {
    __stdio_set_error(stream);
    return -1;
  }

  stream->has_ungetc = 0;
  __stdio_clear_state(stream, FILE_STATE_EOF);
  return 0;
}
