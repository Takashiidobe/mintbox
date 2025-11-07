#include "./internal.h"
#include <stdio.h>
#include <unistd.h>

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
  if (size == 0 || nmemb == 0)
    return 0;

  size_t total_bytes = size * nmemb;
  long ret = write((short)stream->handle, ptr, (long)total_bytes);
  if (ret <= 0)
    return 0;

  return (size_t)(ret / (long)size);
}
