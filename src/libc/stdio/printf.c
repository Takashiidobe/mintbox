#include <stdarg.h>
#include <stdio.h>

int vprintf(const char *format, va_list ap) {
  return vfprintf(stdout, format, ap);
}

int printf(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = vprintf(format, ap);
  va_end(ap);
  return result;
}
