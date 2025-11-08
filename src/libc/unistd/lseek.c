#include <errno.h>
#include <limits.h>
#include <mint/mintbind.h>
#include <sys/types.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence) {
  int16_t mode;

  switch (whence) {
  case SEEK_SET:
    mode = 0;
    break;
  case SEEK_CUR:
    mode = 1;
    break;
  case SEEK_END:
    mode = 2;
    break;
  default:
    errno = EINVAL;
    return -1;
  }

  if (offset < (off_t)INT32_MIN || offset > (off_t)INT32_MAX) {
    errno = EOVERFLOW;
    return -1;
  }

  int32_t ret = Fseek((int32_t)offset, (int16_t)fd, mode);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return (off_t)ret;
}
