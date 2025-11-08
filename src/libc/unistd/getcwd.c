#include <errno.h>
#include <limits.h>
#include <mint/mintbind.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

char *getcwd(char *buf, size_t size) {
  if (size == 0) {
    errno = EINVAL;
    return NULL;
  }

  char *out = buf;
  if (!out) {
    out = malloc(size);
    if (!out) {
      errno = ENOMEM;
      return NULL;
    }
  }

  int16_t len = (size > (size_t)INT_MAX + 1) ? INT_MAX : (int16_t)size;
  int32_t ret = Dgetcwd((int8_t *)out, 0, len);
  if (ret < 0) {
    int saved = (int)-ret;
    if (!buf)
      free(out);
    errno = saved;
    return NULL;
  }
  return out;
}
