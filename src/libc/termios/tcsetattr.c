#include "../gemdos/file.h"
#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define VTIME_MS 100

static inline int fcntl(int fd, void *arg, int cmd) {
  long r = Fcntl(fd, (long)arg, cmd);
  if (r < 0) {
    __set_errno((int)-r);
    return -1;
  }
  return 0;
}

static inline void apply_iflag_oflag_cflag_to_sg(
    const struct termios *tio, struct sgttyb *sg,
    short *out_flags, /* _TF_* driver flags (STOPBITS, CAR, BRKINT, CHARBITS) */
    short *out_state) /* _TS_* driver state (HPCL) */
{
  /* Start from a clean slate for the bits we control. */
  sg->sg_flags &= ~(CRMOD | TANDEM | RTSCTS | EVENP | ODDP | TOSTOP | NOFLSH |
                    ECHOCTL | RAW | CBREAK | ECHO);

  /* iflag -> sg */
  if (tio->c_iflag & ICRNL)
    sg->sg_flags |= CRMOD;
  if ((tio->c_iflag & (IXON | IXOFF)) == (IXON | IXOFF))
    sg->sg_flags |= TANDEM;

  /* cflag (flow control / parity) -> sg */
  if (tio->c_cflag & CRTSCTS)
    sg->sg_flags |= RTSCTS;
  if (tio->c_cflag & PARENB)
    sg->sg_flags |= (tio->c_cflag & PARODD) ? ODDP : EVENP;

  /* lflag (local modes) -> sg RAW/CBREAK/ECHO & misc */
  sg->sg_flags |= (tio->c_lflag & (TOSTOP | NOFLSH | ECHOCTL | ECHO));
  if (tio->c_lflag & ISIG) {
    if (!(tio->c_lflag & ICANON))
      sg->sg_flags |= CBREAK;
  } else {
    sg->sg_flags |= RAW;
  }

  /* Driver flags and state derived from termios c_iflag/c_cflag. */
  short flags = 0;
  flags |= (tio->c_cflag & CSTOPB) ? _TF_2STOP : _TF_1STOP;
  flags |= (tio->c_cflag & CLOCAL) ? 0 : _TF_CAR;
  flags |= (tio->c_iflag & BRKINT) ? _TF_BRKINT : 0;
  flags |= (tio->c_cflag & CSIZE); /* character size via _TF_CHARBITS */

  short state = 0;
  if (tio->c_cflag & HUPCL)
    state |= _TS_HPCL;

  *out_flags = flags;
  *out_state = state;
}

static inline void load_speeds_chars_from_termios(const struct termios *tio,
                                                  struct sgttyb *sg,
                                                  struct tchars *t,
                                                  struct ltchars *lt) {
  sg->sg_ispeed = tio->_c_ispeed;
  sg->sg_ospeed = tio->_c_ospeed;

  t->t_eofc = tio->c_cc[VEOF];
  t->t_brkc = tio->c_cc[VEOL];
  sg->sg_erase = tio->c_cc[VERASE];
  t->t_intrc = tio->c_cc[VINTR];
  sg->sg_kill = tio->c_cc[VKILL];
  t->t_quitc = tio->c_cc[VQUIT];
  t->t_startc = tio->c_cc[VSTART];
  t->t_stopc = tio->c_cc[VSTOP];

  lt->t_suspc = tio->c_cc[VSUSP];
  lt->t_lnextc = tio->c_cc[VLNEXT];
  lt->t_werasc = tio->c_cc[VWERASE];
  lt->t_dsuspc = tio->c_cc[VDSUSP];
  lt->t_rprntc = tio->c_cc[VREPRINT];
  lt->t_flushc = tio->c_cc[VFLUSHO];
}

static inline void compute_vmin_payload(const struct termios *tio,
                                        unsigned short vmin_out[2]) {
  if (tio->c_cc[VMIN]) {
    /* Byte-count mode, ignore VTIME when VMIN is set. */
    vmin_out[0] = (unsigned char)tio->c_cc[VMIN];
    vmin_out[1] = 0;
  } else {
    /* Timeout mode: VMIN=1, VTIME in milliseconds. */
    vmin_out[0] = 1;
    vmin_out[1] = (unsigned short)(tio->c_cc[VTIME] * VTIME_MS);
  }
}

int tcsetattr(int fd, int action, const struct termios *stp) {
  struct sgttyb sg;
  struct tchars t;
  struct ltchars lt;
  short flags, state;
  unsigned short vmin[2];
  long bits[2];

  /* Read current settings we’re about to modify. */
  if (fcntl(fd, &sg, TIOCGETP) < 0)
    return -1;
  if (fcntl(fd, &lt, TIOCGLTC) < 0)
    return -1;

  /* Set line discipline first. */
  if (ioctl(fd, TIOCSETD, (void *)&stp->c_line) < 0) {
    __set_errno(ENOTTY);
    return -1;
  }

  /* Derive sg flags, driver flags/state from termios. */
  apply_iflag_oflag_cflag_to_sg(stp, &sg, &flags, &state);

  /* Populate speeds and cc maps. */
  load_speeds_chars_from_termios(stp, &sg, &t, &lt);

  /* VMIN/VTIME payload for TIOCSVMIN. */
  compute_vmin_payload(stp, vmin);

  /* Commit struct sgttyb according to action. */
  switch (action) {
  case TCSAFLUSH:
    tcflush(fd, TCIFLUSH);
    /* fallthrough */
  case TCSADRAIN:
    if (fcntl(fd, &sg, TIOCSETN) < 0)
      return -1;
    break;
  case TCSANOW:
    if (fcntl(fd, &sg, TIOCSETN) < 0)
      return -1;
    break;
  default:
    __set_errno(EINVAL);
    return -1;
  }

  /* Push control chars. */
  if (fcntl(fd, &t, TIOCSETC) < 0)
    return -1;
  if (fcntl(fd, &lt, TIOCSLTC) < 0)
    return -1;

  /* Try bulk update of driver flags, then fallback to the older API. */
  bits[0] = flags;
  bits[1] = _TF_STOPBITS | _TF_CHARBITS | _TF_CAR | _TF_BRKINT;
  if (Fcntl(fd, (long)&bits, TIOCSFLAGSB) < 0) {
    short sflags = 0;
    Fcntl(fd, (long)&sflags, TIOCGFLAGS);
    sflags &= ~(_TF_STOPBITS | _TF_CHARBITS);
    sflags |= (flags & (_TF_STOPBITS | _TF_CHARBITS));
    Fcntl(fd, (long)&sflags, TIOCSFLAGS);
  }

  /* Set VMIN/VTIME and line state (e.g., HPCL). */
  Fcntl(fd, (long)&vmin, TIOCSVMIN);
  bits[0] = state;
  bits[1] = _TS_HPCL;
  Fcntl(fd, (long)&bits, TIOCSSTATEB);

  return 0;
}
