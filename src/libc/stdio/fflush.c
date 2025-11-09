#include "./internal.h"
#include <mint/mintbind.h>
#include <stdio.h>

static int fflush_single(FILE *stream) {
  if (!stream)
    return EOF;

  if (stream->handle < 0)
    return 0;

  long ret = Fflush((short)stream->handle);
  if (ret < 0) {
    __stdio_set_error(stream);
    return EOF;
  }
  return 0;
}

int fflush(FILE *stream) {
  if (!stream) {
    int result = 0;

    FILE *standard_streams[] = {stdout, stderr};
    for (unsigned i = 0;
         i < sizeof(standard_streams) / sizeof(standard_streams[0]); ++i) {
      if (fflush_single(standard_streams[i]) == EOF)
        result = EOF;
    }

    FILE *pool = __stdio_file_pool();
    int pool_size = __stdio_file_pool_size();
    for (int i = 0; i < pool_size; ++i) {
      FILE *file = &pool[i];
      if (!(file->flags & FILE_FLAG_INUSE) || (file->flags & FILE_FLAG_STATIC))
        continue;
      if (fflush_single(file) == EOF)
        result = EOF;
    }

    return result;
  }

  return fflush_single(stream);
}
