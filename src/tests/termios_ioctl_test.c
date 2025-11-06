#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "../libc/gemdos/file.h"

static bool test_tiocgwinsz(void) {
  struct winsize ws;
  int rc = ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
  if (rc == -1) {
    perror("ioctl(TIOCGWINSZ)");
    return false;
  }
  if (ws.ws_col == 0 || ws.ws_row == 0) {
    fprintf(stderr, "ioctl returned zero geometry: cols=%u rows=%u\n",
            ws.ws_col, ws.ws_row);
    return false;
  }
  return true;
}

static bool dump_ioctl_sequence(void) {
  struct sgttyb sg;
  struct tchars tc;
  struct ltchars lt;
  unsigned short vmin[2];
  long flags_bits[2];
  long state_bits[2];
  int line = 0;

  puts("Fcntl TIOCGETP");
  long r = Fcntl((short)STDIN_FILENO, (long)&sg, TIOCGETP);
  if (r < 0) {
    errno = (int)-r;
    perror("Fcntl(TIOCGETP)");
    return false;
  }

  puts("Fcntl TIOCGLTC");
  r = Fcntl((short)STDIN_FILENO, (long)&lt, TIOCGLTC);
  if (r < 0) {
    errno = (int)-r;
    perror("Fcntl(TIOCGLTC)");
    return false;
  }

  puts("Fcntl TIOCGETC");
  r = Fcntl((short)STDIN_FILENO, (long)&tc, TIOCGETC);
  if (r < 0) {
    errno = (int)-r;
    perror("Fcntl(TIOCGETC)");
    return false;
  }

  puts("ioctl TIOCGETD");
  if (ioctl(STDIN_FILENO, TIOCGETD, &line) == -1) {
    perror("ioctl(TIOCGETD)");
    return false;
  }

  puts("Fcntl TIOCGVMIN");
  r = Fcntl((short)STDIN_FILENO, (long)&vmin, TIOCGVMIN);
  if (r < 0) {
    errno = (int)-r;
    perror("Fcntl(TIOCGVMIN)");
    return false;
  }

  puts("Fcntl TIOCGFLAGS");
  short simple = 0;
  r = Fcntl((short)STDIN_FILENO, (long)&simple, TIOCGFLAGS);
  if (r < 0) {
    errno = (int)-r;
    perror("Fcntl(TIOCGFLAGS)");
    return false;
  }

  puts("Fcntl TIOCGSTATE");
  r = Fcntl((short)STDIN_FILENO, (long)&state_bits, TIOCGSTATE);
  if (r < 0) {
    errno = (int)-r;
    perror("Fcntl(TIOCGSTATE)");
    return false;
  }

  puts("ioctl TIOCGETD");
  bool have_line = true;
  if (ioctl(STDIN_FILENO, TIOCGETD, &line) == -1) {
    perror("ioctl(TIOCGETD) (ignored)");
    have_line = false;
  }

  if (have_line) {
    puts("ioctl TIOCSETD");
    if (ioctl(STDIN_FILENO, TIOCSETD, &line) == -1) {
      perror("ioctl(TIOCSETD)");
      return false;
    }
  } else {
    puts("skipping TIOCSETD (unsupported)");
  }

  puts("Fcntl TIOCSETN");
  r = Fcntl((short)STDIN_FILENO, (long)&sg, TIOCSETN);
  if (r < 0) {
    errno = (int)-r;
    perror("Fcntl(TIOCSETN)");
    return false;
  }

  puts("Fcntl TIOCSETC");
  r = Fcntl((short)STDIN_FILENO, (long)&tc, TIOCSETC);
  if (r < 0) {
    errno = (int)-r;
    perror("Fcntl(TIOCSETC)");
    return false;
  }

  puts("Fcntl TIOCSLTC");
  r = Fcntl((short)STDIN_FILENO, (long)&lt, TIOCSLTC);
  if (r < 0) {
    errno = (int)-r;
    perror("Fcntl(TIOCSLTC)");
    return false;
  }

  flags_bits[0] = simple;
  flags_bits[1] = _TF_STOPBITS | _TF_CHARBITS | _TF_CAR | _TF_BRKINT;

  puts("Fcntl TIOCSFLAGSB");
  r = Fcntl((short)STDIN_FILENO, (long)&flags_bits, TIOCSFLAGSB);
  if (r < 0) {
    errno = (int)-r;
    perror("Fcntl(TIOCSFLAGSB)");
    return false;
  }

  puts("Fcntl TIOCSVMIN");
  r = Fcntl((short)STDIN_FILENO, (long)&vmin, TIOCSVMIN);
  if (r < 0) {
    errno = (int)-r;
    perror("Fcntl(TIOCSVMIN)");
    return false;
  }

  puts("Fcntl TIOCSSTATEB");
  r = Fcntl((short)STDIN_FILENO, (long)&state_bits, TIOCSSTATEB);
  if (r < 0) {
    errno = (int)-r;
    perror("Fcntl(TIOCSSTATEB)");
    return false;
  }

  puts("Sequence complete");
  return true;
}

int main(void) {
  bool ok = true;

  ok &= test_tiocgwinsz();
  ok &= dump_ioctl_sequence();

  return ok ? 0 : 1;
}
