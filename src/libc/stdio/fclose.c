#include "./internal.h"
#include <mint/mintbind.h>

int fclose(FILE *stream) {
  if (!stream)
    return EOF;

  if (stream->flags & FILE_FLAG_STATIC)
    return 0;

  long ret = Fclose((short)stream->handle);
  __stdio_release_file(stream);
  return ret < 0 ? EOF : 0;
}
