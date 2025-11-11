#include <errno.h>
#include <fcntl.h>
#include <mint/mintbind.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

static bool cmd_uses_ptr(int cmd) {
  switch (cmd) {
  case F_GETLK:
  case F_SETLK:
  case F_SETLKW:
    return true;
  default:
    return false;
  }
}

static bool cmd_uses_value(int cmd) {
  switch (cmd) {
  case F_DUPFD:
  case F_DUPFD_CLOEXEC:
  case F_SETFD:
  case F_SETFL:
  case F_SETOWN:
    return true;
  default:
    return false;
  }
}

int fcntl(int fd, int cmd, ...) {
  if (fd < 0) {
    errno = EBADF;
    return -1;
  }

  va_list ap;
  va_start(ap, cmd);

  int32_t arg = 0;
  if (cmd_uses_ptr(cmd)) {
    void *ptr = va_arg(ap, void *);
    arg = (int32_t)(intptr_t)ptr;
  } else if (cmd_uses_value(cmd)) {
    arg = (int32_t)va_arg(ap, int);
  }

  va_end(ap);

  int32_t ret = Fcntl((int16_t)fd, arg, (int16_t)cmd);
  if (ret == ELOCKED)
    ret = EACCES;

  if (ret >= 0)
    return (int)ret;

  errno = (int)-ret;
  return -1;
}
