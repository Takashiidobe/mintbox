#include "../gemdos/file.h"
#include <errno.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

int ftruncate(int fd, off_t length) {
  if (fd < 0) {
    errno = EBADF;
    return -1;
  }

  int32_t result = Fcntl((int16_t)fd, (int32_t)length, FTRUNCATE);
  if (result < 0) {
    errno = (int)-result;
    return -1;
  }
  return 0;
}
