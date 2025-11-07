#include "../gemdos/file.h"
#include <errno.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

int tcflush(int fd, int queue_selector) {
  if (fd < 0) {
    errno = EBADF;
    return -1;
  }

  int16_t selector;
  switch (queue_selector) {
  case TCIFLUSH:
  case TCOFLUSH:
  case TCIOFLUSH:
    selector = queue_selector;
    break;
  default:
    errno = EINVAL;
    return -1;
  }

  int32_t result = Fcntl((int16_t)fd, (intptr_t)&selector, (int16_t)TIOCFLUSH);
  if (result < 0) {
    errno = (int)-result;
    return -1;
  }

  return 0;
}
