#include "../gemdos/file.h"
#include <errno.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

int tcgetattr(int fd, struct termios *termios_p) {
  if (fd < 0) {
    errno = EBADF;
    return -1;
  }
  if (!termios_p) {
    errno = EINVAL;
    return -1;
  }

  struct termios native;
  int32_t result =
      Fcntl((int16_t)fd, (int32_t)(intptr_t)&native, (int16_t)TIOCGETP);
  if (result < 0) {
    errno = (int)-result;
    return -1;
  }

  *termios_p = native;
  return 0;
}
