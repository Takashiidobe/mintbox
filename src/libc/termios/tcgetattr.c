#include "../gemdos/file.h"
#include "./internal.h"
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define VTIME_MS 100

static void default_tchars(struct tchars *tc) {
  tc->t_intrc = CINTR;
  tc->t_quitc = CQUIT;
  tc->t_startc = CSTART;
  tc->t_stopc = CSTOP;
  tc->t_eofc = CEOF;
  tc->t_brkc = CEOL;
}

int tcgetattr(int fd, struct termios *termios_p) {
  if (fd < 0) {
    errno = EBADF;
    return -1;
  }
  if (!termios_p) {
    errno = EINVAL;
    return -1;
  }

  struct sgttyb sg;
  struct tchars tc;
  struct ltchars lt;
  unsigned short vmin[2] = {0, 0};
  short simple_flags = 0;
  long state_bits[2] = {0, 0};
  unsigned short tty_flags = 0;
  unsigned short state = 0;

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

  result = Fcntl((int16_t)fd, (int32_t)(intptr_t)&tc, (int16_t)TIOCGETC);
  if (result < 0) {
    default_tchars(&tc);
  }

  result = Fcntl((int16_t)fd, (int32_t)(intptr_t)&vmin, (int16_t)TIOCGVMIN);
  if (result < 0) {
    vmin[0] = 1;
    vmin[1] = 0;
  }

  result =
      Fcntl((int16_t)fd, (int32_t)(intptr_t)&simple_flags, (int16_t)TIOCGFLAGS);
  if (result >= 0)
    tty_flags = (unsigned short)simple_flags;

  result =
      Fcntl((int16_t)fd, (int32_t)(intptr_t)&state_bits, (int16_t)TIOCGSTATE);
  if (result >= 0)
    state = (unsigned short)state_bits[0];

  memset(termios_p, 0, sizeof(*termios_p));

  termios_p->_c_ispeed = (unsigned short)(unsigned char)sg.sg_ispeed;
  termios_p->_c_ospeed = (unsigned short)(unsigned char)sg.sg_ospeed;

  termios_p->c_cc[VERASE] = (unsigned char)sg.sg_erase;
  termios_p->c_cc[VKILL] = (unsigned char)sg.sg_kill;

  termios_p->c_cc[VINTR] = (unsigned char)tc.t_intrc;
  termios_p->c_cc[VQUIT] = (unsigned char)tc.t_quitc;
  termios_p->c_cc[VSTART] = (unsigned char)tc.t_startc;
  termios_p->c_cc[VSTOP] = (unsigned char)tc.t_stopc;
  termios_p->c_cc[VEOF] = (unsigned char)tc.t_eofc;
  termios_p->c_cc[VEOL] = (unsigned char)tc.t_brkc;

  termios_p->c_cc[VSUSP] = (unsigned char)lt.t_suspc;
  termios_p->c_cc[VDSUSP] = (unsigned char)lt.t_dsuspc;
  termios_p->c_cc[VREPRINT] = (unsigned char)lt.t_rprntc;
  termios_p->c_cc[VFLUSHO] = (unsigned char)lt.t_flushc;
  termios_p->c_cc[VWERASE] = (unsigned char)lt.t_werasc;
  termios_p->c_cc[VLNEXT] = (unsigned char)lt.t_lnextc;

  if (vmin[1]) {
    termios_p->c_cc[VMIN] = 0;
    unsigned int vtime = vmin[1] / VTIME_MS;
    if (vtime > 255)
      vtime = 255;
    termios_p->c_cc[VTIME] = (unsigned char)vtime;
  } else {
    termios_p->c_cc[VMIN] = (unsigned char)vmin[0];
    termios_p->c_cc[VTIME] = 0;
  }

  int line = 0;
  if (ioctl(fd, TIOCGETD, &line) == 0)
    termios_p->c_line = line;
  else
    termios_p->c_line = 0;

  unsigned short sg_flags = (unsigned short)sg.sg_flags;

  termios_p->c_cflag = CREAD;

  switch (tty_flags & _TF_CHARBITS) {
  case _TF_5BIT:
    termios_p->c_cflag |= CS5;
    break;
  case _TF_6BIT:
    termios_p->c_cflag |= CS6;
    break;
  case _TF_7BIT:
    termios_p->c_cflag |= CS7;
    break;
  default:
    termios_p->c_cflag |= CS8;
    break;
  }

  if ((tty_flags & _TF_STOPBITS) == _TF_2STOP)
    termios_p->c_cflag |= CSTOPB;

  if (!(tty_flags & _TF_CAR))
    termios_p->c_cflag |= CLOCAL;

  if (state & _TS_HPCL)
    termios_p->c_cflag |= HUPCL;

  if (sg_flags & RTSCTS)
    termios_p->c_cflag |= CRTSCTS;

  if (sg_flags & EVENP) {
    termios_p->c_cflag |= PARENB;
    termios_p->c_cflag &= ~PARODD;
  } else if (sg_flags & ODDP) {
    termios_p->c_cflag |= (PARENB | PARODD);
  }

  termios_p->c_iflag = 0;
  termios_p->c_oflag = 0;
  termios_p->c_lflag = 0;

  if (tty_flags & _TF_BRKINT)
    termios_p->c_iflag |= BRKINT;

  if (sg_flags & TANDEM)
    termios_p->c_iflag |= (IXON | IXOFF);

  if (sg_flags & CRMOD) {
    termios_p->c_iflag |= ICRNL;
    termios_p->c_oflag |= (OPOST | ONLCR);
  }

  if (sg_flags & ECHO)
    termios_p->c_lflag |= ECHO;
  if (sg_flags & NOFLSH)
    termios_p->c_lflag |= NOFLSH;
  if (sg_flags & TOSTOP)
    termios_p->c_lflag |= TOSTOP;
  if (sg_flags & ECHOCTL)
    termios_p->c_lflag |= ECHOCTL;

  if (sg_flags & RAW) {
    termios_p->c_lflag &= ~(ICANON | ISIG | IEXTEN);
    termios_p->c_iflag = 0;
    termios_p->c_oflag = 0;
  } else {
    termios_p->c_lflag |= IEXTEN;
    if (sg_flags & CBREAK) {
      termios_p->c_lflag |= ISIG;
    } else {
      termios_p->c_lflag |= (ICANON | ISIG);
    }
  }

  __termios_shadow_apply(fd, termios_p);
  return 0;
}
