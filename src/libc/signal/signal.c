#include "../gemdos/process.h"
#include <errno.h>
#include <signal.h>
#include <stdint.h>

__sighandler_t signal(int sig, __sighandler_t handler) {
  if (sig <= 0 || sig >= __NSIG) {
    errno = EINVAL;
    return SIG_ERR;
  }

  int32_t previous = Psignal((int16_t)sig, (int32_t)(intptr_t)handler);
  if (previous < 0) {
    errno = (int)-previous;
    return SIG_ERR;
  }

  return (__sighandler_t)(intptr_t)previous;
}
