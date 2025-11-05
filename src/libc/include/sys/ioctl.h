#ifndef LIBC_SYS_IOCTL_H
#define LIBC_SYS_IOCTL_H

#include <sys/types.h>

struct winsize {
  unsigned short ws_row;
  unsigned short ws_col;
  unsigned short ws_xpixel;
  unsigned short ws_ypixel;
};

#define _IOGROUP_T 'T'
#define _IOGROUP_F 'F'
#define _IOGROUP_P 'P'
#define _IOGROUP_M 'M'
#define _IOGROUP_c 'c'

#define _IO(g, n) (((g) << 8) | (n))

#define TIOCGETP _IO(_IOGROUP_T, 0)
#define TIOCSETN _IO(_IOGROUP_T, 1)
#define TIOCGETC _IO(_IOGROUP_T, 2)
#define TIOCSETC _IO(_IOGROUP_T, 3)
#define TIOCGLTC _IO(_IOGROUP_T, 4)
#define TIOCSLTC _IO(_IOGROUP_T, 5)
#define TIOCGPGRP _IO(_IOGROUP_T, 6)
#define TIOCSPGRP _IO(_IOGROUP_T, 7)
#define TIOCFLUSH _IO(_IOGROUP_T, 8)
#define TIOCSTOP _IO(_IOGROUP_T, 9)
#define TIOCSTART _IO(_IOGROUP_T, 10)
#define TIOCGWINSZ _IO(_IOGROUP_T, 11)
#define TIOCSWINSZ _IO(_IOGROUP_T, 12)
#define TIOCGXKEY _IO(_IOGROUP_T, 13)
#define TIOCSXKEY _IO(_IOGROUP_T, 14)
#define TIOCIBAUD _IO(_IOGROUP_T, 18)
#define TIOCOBAUD _IO(_IOGROUP_T, 19)
#define TIOCCBRK _IO(_IOGROUP_T, 20)
#define TIOCSBRK _IO(_IOGROUP_T, 21)
#define TIOCGFLAGS _IO(_IOGROUP_T, 22)
#define TIOCSFLAGS _IO(_IOGROUP_T, 23)
#define TIOCOUTQ _IO(_IOGROUP_T, 24)
#define TIOCSETP _IO(_IOGROUP_T, 25)
#define TIOCHPCL _IO(_IOGROUP_T, 26)
#define TIOCCAR _IO(_IOGROUP_T, 27)
#define TIOCNCAR _IO(_IOGROUP_T, 28)
#define TIOCWONLINE _IO(_IOGROUP_T, 29)
#define TIOCSFLAGSB _IO(_IOGROUP_T, 30)
#define TIOCGSTATE _IO(_IOGROUP_T, 31)
#define TIOCSSTATEB _IO(_IOGROUP_T, 32)
#define TIOCGVMIN _IO(_IOGROUP_T, 33)
#define TIOCSVMIN _IO(_IOGROUP_T, 34)
#define TIOCGHUPCL _IO(_IOGROUP_T, 98)
#define TIOCSHUPCL _IO(_IOGROUP_T, 99)
#define TIOCGSOFTCAR _IO(_IOGROUP_T, 100)
#define TIOCSSOFTCAR _IO(_IOGROUP_T, 101)
#define TIOCBUFFER _IO(_IOGROUP_T, 128)
#define TIOCCTLMAP _IO(_IOGROUP_T, 129)
#define TIOCCTLGET _IO(_IOGROUP_T, 130)
#define TIOCCTLSET _IO(_IOGROUP_T, 131)
#define TIOCCTLSFAST _IO(_IOGROUP_T, 132)
#define TIOCCTLSSLOW _IO(_IOGROUP_T, 133)
#define TIONOTSEND _IO(_IOGROUP_T, 134)
#define TIOCERROR _IO(_IOGROUP_T, 135)
#define TIOCSCTTY _IO(_IOGROUP_T, 245)
#define TIOCLBIS _IO(_IOGROUP_T, 246)
#define TIOCLBIC _IO(_IOGROUP_T, 247)
#define TIOCMGET _IO(_IOGROUP_T, 248)
#define TIOCCDTR _IO(_IOGROUP_T, 249)
#define TIOCSDTR _IO(_IOGROUP_T, 250)
#define TIOCNOTTY _IO(_IOGROUP_T, 251)
#define TIOCGETD _IO(_IOGROUP_T, 252)
#define TIOCSETD _IO(_IOGROUP_T, 253)
#define TIOCLGET _IO(_IOGROUP_T, 254)
#define TIOCLSET _IO(_IOGROUP_T, 255)

#define TIOCM_LE 0001
#define TIOCM_DTR 0002
#define TIOCM_RTS 0004
#define TIOCM_ST 0010
#define TIOCM_SR 0020
#define TIOCM_CTS 0040
#define TIOCM_CAR 0100
#define TIOCM_CD TIOCM_CAR
#define TIOCM_RNG 0200
#define TIOCM_RI TIOCM_RNG
#define TIOCM_DSR 0400

#define NTTYDISC 1

#define FSTAT _IO(_IOGROUP_F, 0)
#define FIONREAD _IO(_IOGROUP_F, 1)
#define FIONWRITE _IO(_IOGROUP_F, 2)
#define FUTIME _IO(_IOGROUP_F, 3)
#define FTRUNCATE _IO(_IOGROUP_F, 4)
#define FIOEXCEPT _IO(_IOGROUP_F, 5)
#define FSTAT64 _IO(_IOGROUP_F, 6)
#define FUTIME_UTC _IO(_IOGROUP_F, 7)
#define FIONBIO _IO(_IOGROUP_F, 8)

#define PPROCADDR _IO(_IOGROUP_P, 1)
#define PBASEADDR _IO(_IOGROUP_P, 2)
#define PCTXTSIZE _IO(_IOGROUP_P, 3)
#define PSETFLAGS _IO(_IOGROUP_P, 4)
#define PGETFLAGS _IO(_IOGROUP_P, 5)
#define PTRACESFLAGS _IO(_IOGROUP_P, 6)
#define PTRACEGFLAGS _IO(_IOGROUP_P, 7)
#define PTRACEGO _IO(_IOGROUP_P, 8)
#define PTRACEFLOW _IO(_IOGROUP_P, 9)
#define PTRACESTEP _IO(_IOGROUP_P, 10)
#define PTRACE11 _IO(_IOGROUP_P, 11)
#define PLOADINFO _IO(_IOGROUP_P, 12)
#define PFSTAT _IO(_IOGROUP_P, 13)

struct __ploadinfo {
  short fnamelen;
  char *cmdlin;
  char *fname;
};

#define P_ENABLE 1

#define SHMGETBLK _IO(_IOGROUP_M, 0)
#define SHMSETBLK _IO(_IOGROUP_M, 1)

#define TCURSOFF _IO(_IOGROUP_c, 0)
#define TCURSON _IO(_IOGROUP_c, 1)
#define TCURSBLINK _IO(_IOGROUP_c, 2)
#define TCURSSTEADY _IO(_IOGROUP_c, 3)
#define TCURSSRATE _IO(_IOGROUP_c, 4)
#define TCURSGRATE _IO(_IOGROUP_c, 5)
#define TCURSSDELAY _IO(_IOGROUP_c, 6)
#define TCURSGDELAY _IO(_IOGROUP_c, 7)

int ioctl(int fd, unsigned long request, void *arg);

#endif /* LIBC_SYS_IOCTL_H */
