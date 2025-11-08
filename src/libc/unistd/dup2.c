#include <errno.h>
#include <mint/mintbind.h>
#include <stdint.h>
#include <unistd.h>

int dup2(int oldfd, int newfd) {
  if (oldfd < 0 || newfd < 0) {
    errno = EBADF;
    return -1;
  }

  if (oldfd == newfd)
    return newfd;

  int32_t ret = Fforce((int16_t)newfd, (int16_t)oldfd);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return newfd;
}
