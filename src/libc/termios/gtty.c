#include <sys/ioctl.h>

int gtty(int fd, struct sgttyb *tty) { return ioctl(fd, TIOCGETP, tty); }
