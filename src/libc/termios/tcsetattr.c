#include "../gemdos/file.h"
#include <errno.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

int tcsetattr(int fd, int optional_actions, const struct termios *termios_p) {
  if (fd < 0) {
    errno = EBADF;
    return -1;
  }
  if (!termios_p) {
    errno = EINVAL;
    return -1;
  }

  int action = optional_actions;
  if (action == TCSAFLUSH) {
    if (tcflush(fd, TCIFLUSH) < 0)
      return -1;
    action = TCSADRAIN;
  }

  int16_t cmd;
  switch (action) {
  case TCSANOW:
    cmd = TIOCSETN;
    break;
  case TCSADRAIN:
    cmd = TIOCSETP;
    break;
  default:
    errno = EINVAL;
    return -1;
  }

  struct termios native = *termios_p;
  int32_t result = Fcntl((int16_t)fd, (int32_t)(intptr_t)&native, (int16_t)cmd);
  if (result < 0) {
    errno = (int)-result;
    return -1;
  }

  return 0;
}
