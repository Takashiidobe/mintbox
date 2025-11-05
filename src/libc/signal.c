#include <errno.h>
#include <signal.h>

#define SIGNAL_TABLE_SIZE 32

static sighandler_t signal_table[SIGNAL_TABLE_SIZE] = {0};

sighandler_t signal(int sig, sighandler_t handler) {
  if (sig < 0 || sig >= SIGNAL_TABLE_SIZE) {
    errno = EINVAL;
    return SIG_ERR;
  }

  sighandler_t previous = signal_table[sig];
  signal_table[sig] = handler;
  return previous ? previous : SIG_DFL;
}
