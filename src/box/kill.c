#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int parse_decimal(const char *str, long *out) {
  if (!str || !*str) {
    return -1;
  }

  long value = 0;
  for (const char *p = str; *p; ++p) {
    if (*p < '0' || *p > '9') {
      return -1;
    }
    int digit = *p - '0';
    if (value > (LONG_MAX - digit) / 10) {
      errno = ERANGE;
      return -1;
    }
    value = value * 10 + digit;
  }

  *out = value;
  return 0;
}

struct sig_entry {
  const char *name;
  int value;
};

#define SIG_ENTRY(sig) {#sig, sig}, {"SIG" #sig, sig}

static const struct sig_entry sig_table[] = {
#ifdef SIGHUP
    SIG_ENTRY(SIGHUP),
#endif
#ifdef SIGINT
    SIG_ENTRY(SIGINT),
#endif
#ifdef SIGQUIT
    SIG_ENTRY(SIGQUIT),
#endif
#ifdef SIGILL
    SIG_ENTRY(SIGILL),
#endif
#ifdef SIGABRT
    SIG_ENTRY(SIGABRT),
#endif
#ifdef SIGKILL
    SIG_ENTRY(SIGKILL),
#endif
#ifdef SIGALRM
    SIG_ENTRY(SIGALRM),
#endif
#ifdef SIGTERM
    SIG_ENTRY(SIGTERM),
#endif
#ifdef SIGTSTP
    SIG_ENTRY(SIGTSTP),
#endif
#ifdef SIGTTIN
    SIG_ENTRY(SIGTTIN),
#endif
#ifdef SIGTTOU
    SIG_ENTRY(SIGTTOU),
#endif
#ifdef SIGUSR1
    SIG_ENTRY(SIGUSR1),
#endif
#ifdef SIGUSR2
    SIG_ENTRY(SIGUSR2),
#endif
#ifdef SIGPIPE
    SIG_ENTRY(SIGPIPE),
#endif
#ifdef SIGCHLD
    SIG_ENTRY(SIGCHLD),
#endif
#ifdef SIGCONT
    SIG_ENTRY(SIGCONT),
#endif
#ifdef SIGSTOP
    SIG_ENTRY(SIGSTOP),
#endif
};

static int parse_signal(const char *arg, int *out) {
  if (!arg || !*arg) {
    return -1;
  }

  if (*arg == '-') {
    ++arg;
  }

  long val = 0;
  if (parse_decimal(arg, &val) == 0) {
    if (val > INT_MAX) {
      errno = EINVAL;
      return -1;
    }
    *out = (int)val;
    return 0;
  }

  const char *name = arg;
  if (strncmp(name, "SIG", 3) == 0) {
    name += 3;
  }

  for (size_t i = 0; i < sizeof(sig_table) / sizeof(sig_table[0]); ++i) {
    const char *entry = sig_table[i].name;
    const char *cmp = entry;
    if (strncmp(entry, "SIG", 3) == 0) {
      cmp = entry + 3;
    }
    if (strcmp(cmp, name) == 0) {
      *out = sig_table[i].value;
      return 0;
    }
  }

  errno = EINVAL;
  return -1;
}

static long parse_pid(const char *arg) {
  if (!arg || !*arg) {
    errno = EINVAL;
    return -1;
  }

  long pid = 0;
  if (parse_decimal(arg, &pid) < 0 || pid <= 0) {
    errno = EINVAL;
    return -1;
  }

  return pid;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "usage: %s <signal> <pid>\n", argv[0]);
    return 1;
  }

  int signo = 0;
  if (parse_signal(argv[1], &signo) < 0) {
    perror("signal parse");
    return 1;
  }

  long pid = parse_pid(argv[2]);
  if (pid < 0) {
    perror("pid parse");
    return 1;
  }

  if (kill((pid_t)pid, signo) != 0) {
    perror("kill");
    return 1;
  }

  return 0;
}
