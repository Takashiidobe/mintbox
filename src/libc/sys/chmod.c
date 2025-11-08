#include <errno.h>
#include <mint/mintbind.h>
#include <stdint.h>
#include <sys/stat.h>

int chmod(const char *path, mode_t mode) {
  if (!path) {
    errno = EFAULT;
    return -1;
  }

  int32_t ret = Fchmod((char *)path, (int16_t)mode);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return 0;
}

int fchmod(int fd, mode_t mode) {
  int32_t ret = Ffchmod((int16_t)fd, (int16_t)mode);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return 0;
}
