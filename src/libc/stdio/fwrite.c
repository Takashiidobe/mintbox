#include "./internal.h"
#include <mint/mintbind.h>
#include <stdio.h>

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
  if (!stream || !ptr || size == 0 || nmemb == 0)
    return 0;

  if (stream->handle < 0) {
    __stdio_set_error(stream);
    return 0;
  }

  long total_bytes = (long)(size * nmemb);
  long ret = Fwrite((short)stream->handle, total_bytes, (void *)ptr);
  if (ret < 0) {
    __stdio_set_error(stream);
    return 0;
  }

  if (ret == 0)
    return 0;

  if (ret < total_bytes)
    __stdio_set_error(stream);

  return (size_t)(ret / (long)size);
}
