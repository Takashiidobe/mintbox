#ifndef LIBC_TERMIOS_H
#define LIBC_TERMIOS_H

#include <sys/types.h>

typedef unsigned short tcflag_t;
typedef unsigned short speed_t;
typedef unsigned char cc_t;

#define VEOF 0
#define VEOL 1
#define VERASE 2
#define VINTR 3
#define VKILL 4
#define VQUIT 5
#define VSUSP 6
#define VSTART 7
#define VSTOP 8
#define VMIN 9
#define VTIME 10
#define VLNEXT 11
#define VWERASE 12
#define VDSUSP 13
#define VREPRINT 14
#define VFLUSHO 15

#define NCCS (VFLUSHO + 1)

#ifndef CEOF
#define CEOF ('d' & 0x1f)
#endif
#ifndef CEOL
#define CEOL ('m' & 0x1f)
#endif
#ifndef CERASE
#define CERASE ('h' & 0x1f)
#endif
#ifndef CINTR
#define CINTR ('c' & 0x1f)
#endif
#ifndef CKILL
#define CKILL ('u' & 0x1f)
#endif
#ifndef CQUIT
#define CQUIT 28
#endif
#ifndef CSUSP
#define CSUSP ('z' & 0x1f)
#endif
#ifndef CSTART
#define CSTART ('q' & 0x1f)
#endif
#ifndef CSTOP
#define CSTOP ('s' & 0x1f)
#endif
#ifndef CLNEXT
#define CLNEXT ('v' & 0x1f)
#endif
#ifndef CWERASE
#define CWERASE ('w' & 0x1f)
#endif
#ifndef CDSUSP
#define CDSUSP ('y' & 0x1f)
#endif
#ifndef CRPRNT
#define CRPRNT ('r' & 0x1f)
#endif
#ifndef CFLUSHO
#define CFLUSHO ('o' & 0x1f)
#endif

struct termios {
  tcflag_t c_iflag;
  tcflag_t c_oflag;
  tcflag_t c_cflag;
  tcflag_t c_lflag;
  speed_t _c_ispeed;
  speed_t _c_ospeed;
  cc_t c_cc[NCCS];
  int c_line;
};

/* input flags */
#define BRKINT 0x0001
#define IGNBRK 0x0002
#define IGNPAR 0x0004
#define PARMRK 0x0008
#define INPCK 0x0010
#define ISTRIP 0x0020
#define INLCR 0x0040
#define IGNCR 0x0080
#define ICRNL 0x0100
#define IXON 0x0200
#define IXOFF 0x0400
#define IXANY 0x0800

/* output modes */
#define OPOST 0x0001
#define ONLCR 0x0002

/* control modes */
#define CLOCAL 0x0001
#define CREAD 0x0002
#define CS5 0x000C
#define CS6 0x0008
#define CS7 0x0004
#define CS8 0x0000
#define CSIZE 0x000C
#define CSTOPB 0x0040
#define HUPCL 0x0080
#define PARENB 0x0100
#define PARODD 0x0200
#define CRTSCTS 0x2000

/* local modes */
#define ECHOE 0x0001
#define ECHOK 0x0002
#define ECHO 0x0004
#define ECHONL 0x0008
#define ICANON 0x0010
#define ISIG 0x0020
#define NOFLSH 0x0040
#define IEXTEN 0x0080
#define TOSTOP 0x0100
#define ECHOCTL 0x0400

/* actions for tcflow() */
#define TCOOFF 0
#define TCOON 1
#define TCIOFF 2
#define TCION 3

/* actions for tcflush() */
#define TCIFLUSH 0
#define TCOFLUSH 1
#define TCIOFLUSH 3

/* actions for tcsetattr() */
#define TCSANOW 0
#define TCSADRAIN 1
#define TCSAFLUSH 2

/* baud rate codes */
#define B0 0
#define B50 1
#define B75 2
#define B110 3
#define B134 4
#define B135 4
#define B150 5
#define B200 6
#define B300 7
#define B600 8
#define B1200 9
#define B1800 10
#define B2400 11
#define B4800 12
#define B9600 13
#define B19200 14
#define B38400 15
#define B57600 16
#define B115200 17
#define B230400 18
#define B460800 19
#define B921600 20

int tcgetattr(int fd, struct termios *termios_p);
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
int tcflush(int fd, int queue_selector);

#define _TF_STOPBITS 0x0003
#define _TF_1STOP 0x0001
#define _TF_15STOP 0x0002
#define _TF_2STOP 0x0003
#define _TF_CHARBITS 0x000C
#define _TF_8BIT 0x0000
#define _TF_7BIT 0x0004
#define _TF_6BIT 0x0008
#define _TF_5BIT 0x000C
#define _TF_CAR 0x0800
#define _TF_BRKINT 0x0080

#define _TS_BLIND 0x0800
#define _TS_HOLD 0x1000
#define _TS_HPCL 0x4000
#define _TS_COOKED 0x8000

#endif /* LIBC_TERMIOS_H */
