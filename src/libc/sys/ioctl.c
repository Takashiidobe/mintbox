#include "../gemdos/file.h"
#include <errno.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

int ioctl(int fd, unsigned long request, void *arg) {
  if (fd < 0) {
    errno = EBADF;
    return -1;
  }

  unsigned long group = (request >> 8) & 0xFFu;
  if (group == 'F' || group == 'T') {
    int16_t cmd = (int16_t)request;
    int32_t arg_val = (intptr_t)arg;
    int32_t result = Fcntl((int16_t)fd, arg_val, cmd);
    if (result < 0) {
      errno = -result;
      return -1;
    }
    return result;
  }

  errno = ENOTTY;
  return -1;
}
