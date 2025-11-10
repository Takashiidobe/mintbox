#include <errno.h>
#include <signal.h>

static int valid_sig(int sig) { return sig > 0 && sig < __NSIG; }

int sigemptyset(sigset_t *set) {
  if (!set) {
    errno = EINVAL;
    return -1;
  }
  *set = 0;
  return 0;
}

int sigfillset(sigset_t *set) {
  if (!set) {
    errno = EINVAL;
    return -1;
  }
  sigset_t mask = 0;
  for (int sig = 1; sig < __NSIG; ++sig)
    mask |= (sigset_t)1U << sig;
  *set = mask;
  return 0;
}

int sigaddset(sigset_t *set, int sig) {
  if (!set || !valid_sig(sig)) {
    errno = EINVAL;
    return -1;
  }
  *set |= (sigset_t)1U << sig;
  return 0;
}

int sigdelset(sigset_t *set, int sig) {
  if (!set || !valid_sig(sig)) {
    errno = EINVAL;
    return -1;
  }
  *set &= ~((sigset_t)1U << sig);
  return 0;
}

int sigismember(const sigset_t *set, int sig) {
  if (!set || !valid_sig(sig)) {
    errno = EINVAL;
    return -1;
  }
  return ((*set) & ((sigset_t)1U << sig)) ? 1 : 0;
}
