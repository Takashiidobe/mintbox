#include "../gemdos/file.h"
#include "./internal.h"
#include <string.h>

int fprintf(FILE *stream, const char *format, ...) {
  if (!stream || !format)
    return EOF;

  size_t len = strlen(format);
  size_t written = fwrite(format, 1, len, stream);
  return written == len ? (int)written : EOF;
}
