#ifndef LIBC_TERMIOS_H
#define LIBC_TERMIOS_H

#include <sys/types.h>

typedef unsigned int tcflag_t;
typedef unsigned char cc_t;
typedef unsigned int speed_t;

#define NCCS 11

struct termios {
  tcflag_t c_iflag;
  tcflag_t c_oflag;
  tcflag_t c_cflag;
  tcflag_t c_lflag;
  cc_t c_cc[NCCS];
};

#define VINTR 0
#define VQUIT 1
#define VERASE 2
#define VKILL 3
#define VEOF 4
#define VTIME 5
#define VMIN 6

#define BRKINT (1u << 0)
#define ICRNL (1u << 1)
#define INPCK (1u << 2)
#define ISTRIP (1u << 3)
#define IXON (1u << 4)

#define OPOST (1u << 0)

#define CS8 (1u << 0)

#define ECHO (1u << 0)
#define ICANON (1u << 1)
#define IEXTEN (1u << 2)
#define ISIG (1u << 3)

#define TCSANOW 0
#define TCSADRAIN 1
#define TCSAFLUSH 2

int tcgetattr(int fd, struct termios *termios_p);
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);

#endif /* LIBC_TERMIOS_H */
