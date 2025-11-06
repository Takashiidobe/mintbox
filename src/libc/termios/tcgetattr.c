#include "../gemdos/file.h"
#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define VTIME_MS 100

static inline int __fcntl_get(int fd, void *arg, int cmd) {
  long r = Fcntl(fd, (long)arg, cmd);
  if (r < 0) {
    __set_errno((int)-r);
    return -1;
  }
  return 0;
}

static inline tcflag_t compute_iflag(const struct sgttyb *sg, short flags) {
  /* currently only _TF_BRKINT affects iflag */
  tcflag_t iflag = 0;

  if (flags & _TF_BRKINT)
    iflag |= BRKINT;
  if (sg->sg_flags & CRMOD)
    iflag |= ICRNL;

  if (sg->sg_flags & (EVENP | ODDP)) {
    iflag |= INPCK;
  } else if (!(sg->sg_flags & RAW)) {
    iflag |= IGNPAR;
  }

  if (sg->sg_flags & TANDEM)
    iflag |= (IXON | IXOFF);
  if (!(sg->sg_flags & RAW))
    iflag |= IXON;

  return iflag;
}

static inline tcflag_t compute_oflag(const struct sgttyb *sg) {
  return (sg->sg_flags & CRMOD) ? (OPOST | ONLCR) : 0;
}

static inline tcflag_t compute_cflag(const struct sgttyb *sg, short flags,
                                     long state) {
  tcflag_t cflag = CREAD;

  if (!(flags & _TF_CAR))
    cflag |= CLOCAL;
  if (state & _TS_HPCL)
    cflag |= HUPCL;
  if ((flags & _TF_STOPBITS) == _TF_2STOP)
    cflag |= CSTOPB;

  /* Character size from low bits in flags (platform-specific mask). */
  cflag |= (flags & _TF_CHARBITS);

  if (sg->sg_flags & RTSCTS)
    cflag |= CRTSCTS;
  if (sg->sg_flags & EVENP)
    cflag |= PARENB;
  if (sg->sg_flags & ODDP)
    cflag |= (PARENB | PARODD);

  return cflag;
}

static inline tcflag_t compute_lflag(const struct sgttyb *sg) {
  tcflag_t lflag = 0;

  lflag |= (sg->sg_flags & (TOSTOP | NOFLSH | ECHOCTL));
  if (sg->sg_flags & ECHO)
    lflag |= (ECHO | ECHOE | ECHOK);

  if (!(sg->sg_flags & RAW)) {
    lflag |= ISIG;
    if (!(sg->sg_flags & CBREAK))
      lflag |= ICANON;
  }

  return lflag;
}

static inline void compute_vmin_vtime(int fd, cc_t *vmin_out, cc_t *vtime_out) {
  unsigned short vmin_raw[2];

  if (__fcntl_get(fd, &vmin_raw, TIOCGVMIN) < 0) {
    *vmin_out = 1;
    *vtime_out = 0;
    return;
  }

  if (vmin_raw[1]) {
    /* Timeout mode (milliseconds in vmin_raw[1]) */
    unsigned timeout_ticks = vmin_raw[1] / VTIME_MS;
    *vmin_out = 0;
    *vtime_out = (timeout_ticks > 0xff) ? 0xff : (cc_t)timeout_ticks;
  } else {
    /* Byte-count mode */
    *vmin_out = (vmin_raw[0] > 0xff) ? 0xff : (cc_t)vmin_raw[0];
    *vtime_out = 0;
  }
}

int tcgetattr(int fd, struct termios *stp) {
  struct sgttyb sg;
  struct tchars t;
  struct ltchars lt;
  short flags;
  long state;

  if (__fcntl_get(fd, &sg, TIOCGETP) < 0)
    return -1;
  if (__fcntl_get(fd, &t, TIOCGETC) < 0)
    return -1;
  if (__fcntl_get(fd, &lt, TIOCGLTC) < 0)
    return -1;

  if (ioctl(fd, TIOCGETD, &stp->c_line) < 0) {
    __set_errno(errno);
    return -1;
  }

  if (__fcntl_get(fd, &flags, TIOCGFLAGS) < 0)
    flags = 0;
  if (__fcntl_get(fd, &state, TIOCGSTATE) < 0)
    state = 0;

  stp->c_iflag = compute_iflag(&sg, flags);
  stp->c_oflag = compute_oflag(&sg);
  stp->c_cflag = compute_cflag(&sg, flags, state);
  stp->c_lflag = compute_lflag(&sg);

  stp->_c_ispeed = sg.sg_ispeed;
  stp->_c_ospeed = sg.sg_ospeed;

  stp->c_cc[VEOF] = t.t_eofc;
  stp->c_cc[VEOL] = t.t_brkc;
  stp->c_cc[VERASE] = sg.sg_erase;
  stp->c_cc[VINTR] = t.t_intrc;
  stp->c_cc[VKILL] = sg.sg_kill;
  stp->c_cc[VQUIT] = t.t_quitc;
  stp->c_cc[VSUSP] = lt.t_suspc;
  stp->c_cc[VSTART] = t.t_startc;
  stp->c_cc[VSTOP] = t.t_stopc;

  compute_vmin_vtime(fd, &stp->c_cc[VMIN], &stp->c_cc[VTIME]);

  stp->c_cc[VLNEXT] = lt.t_lnextc;
  stp->c_cc[VWERASE] = lt.t_werasc;
  stp->c_cc[VDSUSP] = lt.t_dsuspc;
  stp->c_cc[VREPRINT] = lt.t_rprntc;
  stp->c_cc[VFLUSHO] = lt.t_flushc;

  return 0;
}
