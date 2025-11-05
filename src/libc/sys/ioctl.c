#include "../gemdos/file.h"
#include <errno.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

static int __ioctl_ttydisc = NTTYDISC;
static int __ioctl_ldisc = LLITOUT;
static struct tchars __ioctl_tchars = {CINTR, CQUIT, CSTART, CSTOP, CEOF, CEOL};
static struct ltchars __ioctl_ltchars = {CSUSP, CDSUSP, CRPRNT, CFLUSHO, CWERASE,
                                         CLNEXT};

static int handle_fallback(int fd, unsigned long request, void *arg) {
  if (!isatty(fd)) {
    errno = ENOTTY;
    return -1;
  }

  switch (request) {
  case TIOCGETD:
    if (arg) {
      *(int *)arg = __ioctl_ttydisc;
      return 0;
    }
    errno = EINVAL;
    return -1;
  case TIOCSETD:
    if (arg) {
      __ioctl_ttydisc = *(int *)arg;
      return 0;
    }
    errno = EINVAL;
    return -1;
  case TIOCLGET:
    if (arg) {
      *(int *)arg = __ioctl_ldisc;
      return 0;
    }
    errno = EINVAL;
    return -1;
  case TIOCLSET:
    if (arg) {
      __ioctl_ldisc = *(int *)arg;
      return 0;
    }
    errno = EINVAL;
    return -1;
  case TIOCLBIS:
    if (arg) {
      __ioctl_ldisc |= *(int *)arg;
      return 0;
    }
    errno = EINVAL;
    return -1;
  case TIOCLBIC:
    if (arg) {
      __ioctl_ldisc &= ~(*(int *)arg);
      return 0;
    }
    errno = EINVAL;
    return -1;
  case TIOCGETC:
    if (arg) {
      *(struct tchars *)arg = __ioctl_tchars;
      return 0;
    }
    errno = EINVAL;
    return -1;
  case TIOCSETC:
    if (arg) {
      __ioctl_tchars = *(struct tchars *)arg;
      return 0;
    }
    errno = EINVAL;
    return -1;
  case TIOCGLTC:
    if (arg) {
      *(struct ltchars *)arg = __ioctl_ltchars;
      return 0;
    }
    errno = EINVAL;
    return -1;
  case TIOCSLTC:
    if (arg) {
      __ioctl_ltchars = *(struct ltchars *)arg;
      return 0;
    }
    errno = EINVAL;
    return -1;
  default:
    errno = ENOSYS;
    return -1;
  }
}

int ioctl(int fd, unsigned long request, void *arg) {
  if (fd < 0) {
    errno = EBADF;
    return -1;
  }

  unsigned long group = (request >> 8) & 0xFFu;
  if (group == 'F' || group == 'T') {
    /* Certain tty ioctls are not implemented by MiNT; emulate up front. */
    switch (request) {
    case TIOCGETD:
    case TIOCSETD:
    case TIOCLGET:
    case TIOCLSET:
    case TIOCLBIS:
    case TIOCLBIC:
    case TIOCGETC:
    case TIOCSETC:
    case TIOCGLTC:
    case TIOCSLTC:
      return handle_fallback(fd, request, arg);
    default:
      break;
    }

    int16_t cmd = (int16_t)request;
    int32_t result = Fcntl((int16_t)fd, (int32_t)(intptr_t)arg, cmd);
    if (result >= 0)
      return (int)result;

    if (result != -ENOSYS && result != -EINVAL) {
      errno = (int)-result;
      return -1;
    }

    int fallback = handle_fallback(fd, request, arg);
    if (fallback == 0)
      return 0;
    if (errno != ENOSYS)
      return -1;
  }

  errno = ENOTTY;
  return -1;
}
