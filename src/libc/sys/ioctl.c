#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
#include <mint/mintbind.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

static int __ioctl_ttydisc = NTTYDISC;
static int __ioctl_ldisc = LLITOUT;
static struct tchars __ioctl_tchars = {CINTR, CQUIT, CSTART, CSTOP, CEOF, CEOL};
static struct ltchars __ioctl_ltchars = {CSUSP,   CDSUSP,  CRPRNT,
                                         CFLUSHO, CWERASE, CLNEXT};

static int handle_tty_fallback(int fd, unsigned long request, void *arg) {
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

static int handle_misc_fallback(int fd, unsigned long request, void *arg) {
  switch (request) {
  case FIONBIO: {
    if (!arg) {
      errno = EINVAL;
      return -1;
    }
    int flags = fcntl(fd, F_GETFL);
    if (flags < 0)
      return -1;

    int enable = (*(int *)arg) ? 1 : 0;
    int new_flags = enable ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    if (new_flags == flags)
      return 0;
    if (fcntl(fd, F_SETFL, new_flags) < 0)
      return -1;
    return 0;
  }
  default:
    errno = ENOSYS;
    return -1;
  }
}

int ioctl(int fd, int request, void *arg) {
  if (fd < 0) {
    errno = EBADF;
    return -1;
  }

  unsigned long group = ((unsigned long)request >> 8) & 0xFFu;

  int32_t result =
      Fcntl((int16_t)fd, (int32_t)(intptr_t)arg, (int16_t)request);
  if (result >= 0)
    return (int)result;

  if (result != ENOSYS && result != EINVAL) {
    errno = (int)-result;
    return -1;
  }

  if (handle_misc_fallback(fd, (unsigned long)request, arg) == 0)
    return 0;
  if (errno != ENOSYS)
    return -1;

  if (group == 'T') {
    int tty_status = handle_tty_fallback(fd, (unsigned long)request, arg);
    if (tty_status == 0)
      return 0;
    return -1;
  }

  errno = ENOSYS;
  return -1;
}
