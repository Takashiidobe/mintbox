#include <assert.h>
#include <signal.h>
#include <stddef.h>

int main(void) {
  sigset_t set;
  assert(sigemptyset(&set) == 0);
  assert(sigismember(&set, SIGINT) == 0);
  assert(sigaddset(&set, SIGINT) == 0);
  assert(sigismember(&set, SIGINT) == 1);
  assert(sigdelset(&set, SIGINT) == 0);
  assert(sigismember(&set, SIGINT) == 0);
  assert(sigfillset(&set) == 0);

  sigset_t old;
  assert(sigprocmask(SIG_SETMASK, &set, &old) == 0);
  assert(sigprocmask(SIG_SETMASK, &old, NULL) == 0);

  sigset_t pending;
  assert(sigpending(&pending) == 0);

  return 0;
}
