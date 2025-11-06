#ifndef LIBC_SYSGROUPCTL_H
#define LIBC_SYSGROUPCTL_H

#include <features.h>
#include <sys/types.h>

#define GROUP(g, n) (((g) << 8) | (n))

#define TIOCGETP GROUP('T', 0)
#define TIOCSETN GROUP('T', 1)
#define TIOCGETC GROUP('T', 2)
#define TIOCSETC GROUP('T', 3)
#define TIOCGLTC GROUP('T', 4)
#define TIOCSLTC GROUP('T', 5)
#define TIOCGPGRP GROUP('T', 6)
#define TIOCSPGRP GROUP('T', 7)
#define TIOCFLUSH GROUP('T', 8)
#define TIOCSTOP GROUP('T', 9)
#define TIOCSTART GROUP('T', 10)
#define TIOCGWINSZ GROUP('T', 11)
#define TIOCSWINSZ GROUP('T', 12)
#define TIOCGXKEY GROUP('T', 13)
#define TIOCSXKEY GROUP('T', 14)
#define TIOCIBAUD GROUP('T', 18)
#define TIOCOBAUD GROUP('T', 19)
#define TIOCCBRK GROUP('T', 20)
#define TIOCSBRK GROUP('T', 21)
#define TIOCGFLAGS GROUP('T', 22)
#define TIOCSFLAGS GROUP('T', 23)
#define TIOCOUTQ GROUP('T', 24)
#define TIOCSETP GROUP('T', 25)
#define TIOCHPCL GROUP('T', 26)
#define TIOCCAR GROUP('T', 27)
#define TIOCNCAR GROUP('T', 28)
#define TIOCWONLINE GROUP('T', 29)
#define TIOCSFLAGSB GROUP('T', 30)
#define TIOCGSTATE GROUP('T', 31)
#define TIOCSSTATEB GROUP('T', 32)
#define TIOCGVMIN GROUP('T', 33)
#define TIOCSVMIN GROUP('T', 34)
#define TIOCGHUPCL GROUP('T', 98)
#define TIOCSHUPCL GROUP('T', 99)
#define TIOCGSOFTCAR GROUP('T', 100)
#define TIOCSSOFTCAR GROUP('T', 101)
#define TIOCBUFFER GROUP('T', 128)
#define TIOCCTLMAP GROUP('T', 129)
#define TIOCCTLGET GROUP('T', 130)
#define TIOCCTLSET GROUP('T', 131)
#define TIOCCTLSFAST GROUP('T', 132)
#define TIOCCTLSSLOW GROUP('T', 133)
#define TIONOTSEND GROUP('T', 134)
#define TIOCERROR GROUP('T', 135)
#define TIOCSCTTY GROUP('T', 245)

// These are all faked
#define TIOCLBIS GROUP('T', 246)
#define TIOCLBIC GROUP('T', 247)
#define TIOCMGET GROUP('T', 248)
#define TIOCCDTR GROUP('T', 249)
#define TIOCSDTR GROUP('T', 250)
#define TIOCNOTTY GROUP('T', 251)

// Not implemented in Mint
#define TIOCGETD GROUP('T', 252)
#define TIOCSETD GROUP('T', 253)
#define TIOCLGET GROUP('T', 254)
#define TIOCLSET GROUP('T', 255)

#define TIOCM_LE 0001 // Unsupported
#define TIOCM_DTR 0002
#define TIOCM_RTS 0004
#define TIOCM_ST 0010 // Unsupported
#define TIOCM_SR 0020 // Unsupported
#define TIOCM_CTS 0040
#define TIOCM_CAR 0100
#define TIOCM_CD TIOCM_CAR
#define TIOCM_RNG 0200
#define TIOCM_RI TIOCM_RNG
#define TIOCM_DSR 0400 // Unsupported

#define NTTYDISC 1

#define FSTAT GROUP('F', 0)
#define FIONREAD GROUP('F', 1)
#define FIONWRITE GROUP('F', 2)
#define FUTIME GROUP('F', 3)
#define FTRUNCATE GROUP('F', 4)
#define FIOEXCEPT GROUP('F', 5)
#define FSTAT64 GROUP('F', 6)    // optional, from 1.15.4.
#define FUTIME_UTC GROUP('F', 7) // optional, from 1.15.4.
#define FIONBIO GROUP('F', 8)    // emulation only.

// ioctls for processes
#define PPROCADDR GROUP('P', 1)
#define PBASEADDR GROUP('P', 2)
#define PCTXTSIZE GROUP('P', 3)
#define PSETFLAGS GROUP('P', 4)
#define PGETFLAGS GROUP('P', 5)
#define PTRACESFLAGS GROUP('P', 6)
#define PTRACEGFLAGS GROUP('P', 7)

// enable tracing
#define P_ENABLE (1 << 0)
#define P_DOS (1 << 1)   // unimplemented
#define P_BIOS (1 << 2)  // unimplemented
#define P_XBIOS (1 << 3) // unimplemented

#define PTRACEGO GROUP('P', 8)
#define PTRACEFLOW GROUP('P', 9)
#define PTRACESTEP GROUP('P', 10)
#define PTRACE11 GROUP('P', 11)
#define PLOADINFO GROUP('P', 12)
#define PFSTAT GROUP('P', 13)

// ioctls for shared memory (SHM)
#define SHMGETBLK GROUP('M', 0)
#define SHMSETBLK GROUP('M', 1)

// ioctls for cursor control
#define TCURSOFF GROUP('c', 0)
#define TCURSON GROUP('c', 1)
#define TCURSBLINK GROUP('c', 2)
#define TCURSSTEADY GROUP('c', 3)
#define TCURSSRATE GROUP('c', 4)
#define TCURSGRATE GROUP('c', 5)
#define TCURSSDELAY GROUP('c', 6)
#define TCURSGDELAY GROUP('c', 7)

// c_lfags for termios
#define CRMOD 0x0001
#define CBREAK 0x0002
#define ECHO 0x0004
#define XTABS 0x0008
#define RAW 0x0010
#define LCASE 0x0020 // does nothing
#define NOFLSH 0x0040
#define TOSTOP 0x0100
#define XKEY 0x0200
#define ECHOCTL 0x0400
#define TANDEM 0x1000
#define RTSCTS 0x2000
#define EVENP 0x4000
#define ODDP 0x8000
#define ANYP 0x0000

// fake defines for line discipline
#define LCRTBS 0x0001
#define LCRTERA 0x0002
#define LCRTKIL 0x0004
#define LPRTERA 0x0010
#define LFLUSHO 0x0020
#define LLITOUT 0x0100

// Baud rate constants for serial ports
#define B0 0
#define B50 1
#define B75 2
#define B110 3
#define B134 4
#define B135 4 // Compatibility alias for baud rate 134.5
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
#define EXTA 21

#define VTDELAY 0  // unsupported
#define ALLDELAY 0 // unsupported

struct __ploadinfo {
  short fnamelen;
  char *cmdlin, *fname;
};

struct winsize {
  unsigned short ws_row;
  unsigned short ws_col;
  unsigned short ws_xpixel;
  unsigned short ws_ypixel;
};

struct tchars {
  char t_intrc;
  char t_quitc;
  char t_startc;
  char t_stopc;
  char t_eofc;
  char t_brkc;
};

struct ltchars {
  char t_suspc;
  char t_dsuspc;
  char t_rprntc;
  char t_flushc;
  char t_werasc;
  char t_lnextc;
};

struct sgttyb {
  char sg_ispeed;
  char sg_ospeed;
  char sg_erase;
  char sg_kill;
  short sg_flags;
};

struct xkey {
  short xk_num;
  char xk_def[8];
};

struct _mutimbuf {
  unsigned short actime, acdate; // GEMDOS format
  unsigned short modtime, moddate;
};

int ioctl(int fd, int request, void *arg);
int stty(int, struct sgttyb *);
int gtty(int, struct sgttyb *);

#endif /* LIBC_SYSGROUPCTL_H */
