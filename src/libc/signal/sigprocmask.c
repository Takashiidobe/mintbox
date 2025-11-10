#include <errno.h>
#include <mint/mintbind.h>
#include <signal.h>
#include <stdint.h>

static sigset_t __sigmask_cache;
static int __sigmask_initialized;

static void __sigmask_init(void) {
  if (__sigmask_initialized)
    return;
  int32_t prev = Psigsetmask(0);
  if (prev >= 0) {
    __sigmask_cache = (sigset_t)prev;
    Psigsetmask(prev);
  } else {
    __sigmask_cache = 0;
  }
  __sigmask_initialized = 1;
}

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset) {
  __sigmask_init();

  if (!set) {
    if (oldset)
      *oldset = __sigmask_cache;
    return 0;
  }

  sigset_t newmask = __sigmask_cache;
  switch (how) {
  case SIG_BLOCK:
    newmask |= *set;
    break;
  case SIG_UNBLOCK:
    newmask &= ~(*set);
    break;
  case SIG_SETMASK:
    newmask = *set;
    break;
  default:
    errno = EINVAL;
    return -1;
  }

  int32_t prev = Psigsetmask((int32_t)newmask);
  if (prev < 0) {
    errno = (int)-prev;
    return -1;
  }

  if (oldset)
    *oldset = (sigset_t)prev;
  __sigmask_cache = newmask;
  return 0;
}

int sigpending(sigset_t *set) {
  if (!set) {
    errno = EINVAL;
    return -1;
  }
  int32_t pending = Psigpending();
  if (pending < 0) {
    errno = (int)-pending;
    return -1;
  }
  *set = (sigset_t)pending;
  return 0;
}

int sigsuspend(const sigset_t *mask) {
  sigset_t value = mask ? *mask : 0;
  Psigpause((int32_t)value);
  errno = EINTR;
  return -1;
}
