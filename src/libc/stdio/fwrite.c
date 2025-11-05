#include "../gemdos/file.h"
#include "./internal.h"

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
  if (!stream || !ptr || size == 0 || nmemb == 0)
    return 0;

  size_t total_bytes = size * nmemb;
  long ret = Fwrite((short)stream->handle, (long)total_bytes, ptr);
  if (ret <= 0)
    return 0;

  return (size_t)(ret / (long)size);
}
