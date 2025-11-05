#include <errno.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define TERMIOS_TABLE_SIZE 4

static struct termios termios_table[TERMIOS_TABLE_SIZE];
static unsigned char termios_initialized[TERMIOS_TABLE_SIZE];

static void termios_init_slot(int index) {
  if (termios_initialized[index])
    return;

  struct termios defaults;
  memset(&defaults, 0, sizeof(defaults));
  defaults.c_iflag = BRKINT | ICRNL | IXON;
  defaults.c_oflag = OPOST;
  defaults.c_cflag = CS8;
  defaults.c_lflag = ECHO | ICANON | ISIG;
  defaults.c_cc[VMIN] = 1;
  defaults.c_cc[VTIME] = 0;

  termios_table[index] = defaults;
  termios_initialized[index] = 1;
}

static int termios_index_from_fd(int fd) {
  if (fd < 0 || fd >= TERMIOS_TABLE_SIZE)
    return -1;
  return fd;
}

int tcgetattr(int fd, struct termios *termios_p) {
  if (!termios_p) {
    errno = EINVAL;
    return -1;
  }

  int index = termios_index_from_fd(fd);
  if (index < 0) {
    errno = ENOTTY;
    return -1;
  }

  termios_init_slot(index);
  *termios_p = termios_table[index];
  return 0;
}

int tcsetattr(int fd, int optional_actions, const struct termios *termios_p) {
  (void)optional_actions;

  if (!termios_p) {
    errno = EINVAL;
    return -1;
  }

  int index = termios_index_from_fd(fd);
  if (index < 0) {
    errno = ENOTTY;
    return -1;
  }

  termios_init_slot(index);
  termios_table[index] = *termios_p;
  return 0;
}
