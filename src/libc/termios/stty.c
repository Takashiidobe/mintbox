#include <sys/ioctl.h>

int stty(int fd, struct sgttyb *tty) { return ioctl(fd, TIOCSETP, tty); }
