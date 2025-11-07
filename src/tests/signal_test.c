#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static volatile int seen_sigttoa = 0;

static void sigttou_handler(int signo) {
  if (signo == SIGTTOU) {
    seen_sigttoa = 1;
    puts("SIGTTOU handled");
  }
}

int main(void) {
  if (signal(SIGTTOU, sigttou_handler) == SIG_ERR) {
    perror("signal");
    return 1;
  }

  if (raise(SIGTTOU) != 0) {
    perror("kill");
    return 1;
  }

  if (!seen_sigttoa) {
    fprintf(stderr, "handler never ran\n");
    return 1;
  }

  puts("success");
  return 0;
}
