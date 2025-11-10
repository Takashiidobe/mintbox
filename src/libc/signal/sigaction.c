#include <errno.h>
#include <mint/mintbind.h>
#include <signal.h>
#include <stdint.h>

int sigaction(int sig, const struct sigaction *act, struct sigaction *oldact) {
  if (sig <= 0 || sig >= __NSIG) {
    errno = EINVAL;
    return -1;
  }

  int32_t ret =
      Psigaction((int16_t)sig, (struct sigaction *)(intptr_t)act, oldact);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return 0;
}
