#include "../gemdos/file.h"
#include <errno.h>
#include <stdint.h>
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count) {
  if (count > (size_t)INT32_MAX) {
    errno = EINVAL;
    return -1;
  }

  int32_t ret = Fread((int16_t)fd, (int32_t)count, buf);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return (ssize_t)ret;
}
