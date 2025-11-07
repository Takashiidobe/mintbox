#include <mint/mintbind.h>
#include <stddef.h>
#include <stdio.h>

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  if (!stream || !ptr || size == 0 || nmemb == 0)
    return 0;

  long total = (long)(size * nmemb);
  long ret = Fread(fileno(stream), total, ptr);
  if (ret <= 0)
    return 0;

  return (size_t)(ret / (long)size);
}
