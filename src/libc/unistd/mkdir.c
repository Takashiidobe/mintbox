#include <errno.h>
#include <mint/mintbind.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

int mkdir(const char *path, mode_t mode) {
  (void)mode;

  if (!path) {
    errno = EFAULT;
    return -1;
  }

  int32_t ret = Dcreate(path);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return 0;
}
