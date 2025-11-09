#include "./internal.h"
#include <mint/mintbind.h>
#include <stddef.h>
#include <stdio.h>

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  if (!stream || !ptr || size == 0 || nmemb == 0)
    return 0;

  long total = (long)(size * nmemb);
  if (stream->handle < 0) {
    __stdio_set_error(stream);
    return 0;
  }

  long ret = Fread((short)stream->handle, total, ptr);
  if (ret == 0) {
    __stdio_set_eof(stream);
    return 0;
  }
  if (ret < 0) {
    __stdio_set_error(stream);
    return 0;
  }

  if (ret < total)
    __stdio_set_eof(stream);

  return (size_t)(ret / (long)size);
}
