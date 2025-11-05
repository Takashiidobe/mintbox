#include "../gemdos/file.h"
#include "./internal.h"
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define VTIME_MS 100

int tcsetattr(int fd, int optional_actions, const struct termios *termios_p) {
  if (fd < 0) {
    errno = EBADF;
    return -1;
  }
  if (!termios_p) {
    errno = EINVAL;
    return -1;
  }

  struct sgttyb sg;
  struct ltchars lt;
  struct tchars tc;

  int32_t result =
      Fcntl((int16_t)fd, (int32_t)(intptr_t)&sg, (int16_t)TIOCGETP);
  if (result < 0) {
    errno = (int)-result;
    return -1;
  }

  result = Fcntl((int16_t)fd, (int32_t)(intptr_t)&lt, (int16_t)TIOCGLTC);
  if (result < 0) {
    errno = (int)-result;
    return -1;
  }

  int line = termios_p->c_line;
  if (ioctl(fd, TIOCGETD, &line) == 0) {
    if (line != termios_p->c_line) {
      int new_line = termios_p->c_line;
      if (ioctl(fd, TIOCSETD, &new_line) < 0) {
        errno = ENOTTY;
        return -1;
      }
    }
  }

  sg.sg_flags &=
      ~(CRMOD | TANDEM | RTSCTS | EVENP | ODDP | TOSTOP | NOFLSH | ECHOCTL | RAW |
        CBREAK | ECHO);
  sg.sg_flags |= ((termios_p->c_iflag & ICRNL) ? CRMOD : 0) |
                 (((termios_p->c_iflag & (IXON | IXOFF)) == (IXON | IXOFF))
                      ? TANDEM
                      : 0) |
                 ((termios_p->c_cflag & CRTSCTS) ? RTSCTS : 0);

  unsigned short tf = ((termios_p->c_cflag & CSTOPB) ? _TF_2STOP : _TF_1STOP) |
                      ((termios_p->c_cflag & CLOCAL) ? 0 : _TF_CAR) |
                      ((termios_p->c_iflag & BRKINT) ? _TF_BRKINT : 0) |
                      (termios_p->c_cflag & CSIZE);

  unsigned short state = (termios_p->c_cflag & HUPCL) ? _TS_HPCL : 0;

  sg.sg_flags |= (termios_p->c_cflag & PARENB)
                     ? ((termios_p->c_cflag & PARODD) ? ODDP : EVENP)
                     : 0;

  sg.sg_flags |=
      ((termios_p->c_lflag & (TOSTOP | NOFLSH | ECHOCTL | ECHO)) |
       ((termios_p->c_lflag & ISIG)
            ? ((termios_p->c_lflag & ICANON) ? 0 : CBREAK)
            : RAW));

  sg.sg_ispeed = (char)termios_p->_c_ispeed;
  sg.sg_ospeed = (char)termios_p->_c_ospeed;

  tc.t_eofc = (char)termios_p->c_cc[VEOF];
  tc.t_brkc = (char)termios_p->c_cc[VEOL];
  sg.sg_erase = (char)termios_p->c_cc[VERASE];
  tc.t_intrc = (char)termios_p->c_cc[VINTR];
  sg.sg_kill = (char)termios_p->c_cc[VKILL];
  tc.t_quitc = (char)termios_p->c_cc[VQUIT];
  lt.t_suspc = (char)termios_p->c_cc[VSUSP];
  tc.t_startc = (char)termios_p->c_cc[VSTART];
  tc.t_stopc = (char)termios_p->c_cc[VSTOP];

  unsigned short vmin[2];
  if (termios_p->c_cc[VMIN]) {
    vmin[0] = (unsigned char)termios_p->c_cc[VMIN];
    vmin[1] = 0;
  } else {
    vmin[0] = 1;
    vmin[1] = (unsigned short)termios_p->c_cc[VTIME] * VTIME_MS;
  }

  lt.t_lnextc = (char)termios_p->c_cc[VLNEXT];
  lt.t_werasc = (char)termios_p->c_cc[VWERASE];
  lt.t_dsuspc = (char)termios_p->c_cc[VDSUSP];
  lt.t_rprntc = (char)termios_p->c_cc[VREPRINT];
  lt.t_flushc = (char)termios_p->c_cc[VFLUSHO];

  int action = optional_actions;
  if (action == TCSAFLUSH) {
    if (tcflush(fd, TCIFLUSH) < 0)
      return -1;
    action = TCSADRAIN;
  }

  int16_t cmd;
  switch (action) {
  case TCSANOW:
    cmd = TIOCSETN;
    break;
  case TCSADRAIN:
    cmd = TIOCSETP;
    break;
  default:
    errno = EINVAL;
    return -1;
  }

  result = Fcntl((int16_t)fd, (int32_t)(intptr_t)&sg, cmd);
  if (result < 0) {
    errno = (int)-result;
    return -1;
  }

  result = Fcntl((int16_t)fd, (int32_t)(intptr_t)&tc, (int16_t)TIOCSETC);
  if (result < 0) {
    errno = (int)-result;
    return -1;
  }

  result = Fcntl((int16_t)fd, (int32_t)(intptr_t)&lt, (int16_t)TIOCSLTC);
  if (result < 0) {
    errno = (int)-result;
    return -1;
  }

  long bits[2];
  bits[0] = (long)tf;
  bits[1] = _TF_STOPBITS | _TF_CHARBITS | _TF_CAR | _TF_BRKINT;
  result = Fcntl((int16_t)fd, (int32_t)(intptr_t)&bits, (int16_t)TIOCSFLAGSB);
  if (result < 0) {
    short sflags = 0;
    if (Fcntl((int16_t)fd, (int32_t)(intptr_t)&sflags, (int16_t)TIOCGFLAGS) >= 0) {
      sflags &= ~(_TF_STOPBITS | _TF_CHARBITS);
      sflags |= (short)(tf & (_TF_STOPBITS | _TF_CHARBITS));
      Fcntl((int16_t)fd, (int32_t)(intptr_t)&sflags, (int16_t)TIOCSFLAGS);
    }
  }

  (void)Fcntl((int16_t)fd, (int32_t)(intptr_t)&vmin, (int16_t)TIOCSVMIN);

  long state_bits[2];
  state_bits[0] = (long)state;
  state_bits[1] = _TS_HPCL;
  (void)Fcntl((int16_t)fd, (int32_t)(intptr_t)&state_bits, (int16_t)TIOCSSTATEB);

  __termios_shadow_store(fd, termios_p);
  return 0;
}
