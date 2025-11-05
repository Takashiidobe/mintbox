#include "./gemdos/file.h"
#include <errno.h>
#include <stdint.h>
#include <unistd.h>

int isatty(int fd) {
  if (fd < 0) {
    errno = EBADF;
    return 0;
  }

  if (fd >= 0 && fd <= 2) {
    return 1;
  }

  int32_t ret = Finstat((int16_t)fd);
  if (ret < 0) {
    errno = ENOTTY;
    return 0;
  }

  return 1;
}
