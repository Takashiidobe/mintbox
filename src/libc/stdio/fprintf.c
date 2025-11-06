#include "./internal.h"
#include <errno.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int vfprintf(FILE *stream, const char *format, va_list ap) {
  va_list ap_copy;
  va_copy(ap_copy, ap);
  int len = vsnprintf(NULL, 0, format, ap_copy);
  va_end(ap_copy);
  if (len < 0) {
    errno = EINVAL;
    return EOF;
  }

  size_t buf_size = (size_t)len + 1;
  char stack_buf[128];
  char *buffer = stack_buf;
  if (buf_size > sizeof(stack_buf)) {
    buffer = (char *)malloc(buf_size);
    if (!buffer) {
      errno = ENOMEM;
      return EOF;
    }
  }

  va_list ap_copy2;
  va_copy(ap_copy2, ap);
  int produced = vsnprintf(buffer, buf_size, format, ap_copy2);
  va_end(ap_copy2);
  if (produced < 0) {
    errno = EINVAL;
    if (buffer != stack_buf)
      free(buffer);
    return EOF;
  }

  size_t written = fwrite(buffer, 1, (size_t)produced, stream);

  if (buffer != stack_buf)
    free(buffer);

  if (written != (size_t)produced) {
    return EOF;
  }

  return produced;
}

int fprintf(FILE *stream, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = vfprintf(stream, format, ap);
  va_end(ap);
  return result;
}
