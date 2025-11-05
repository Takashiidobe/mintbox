#include <errno.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

int ioctl(int fd, unsigned long request, void *arg) {
  errno = ENOTTY;
  return -1;
}
