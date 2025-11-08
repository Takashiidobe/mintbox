#include <errno.h>
#include <mint/mintbind.h>
#include <stdint.h>
#include <unistd.h>

int dup(int fd) {
  if (fd < 0) {
    errno = EBADF;
    return -1;
  }

  int32_t ret = Fdup((int16_t)fd);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return (int)ret;
}
