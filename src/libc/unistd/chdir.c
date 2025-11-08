#include <errno.h>
#include <mint/mintbind.h>
#include <stdint.h>
#include <unistd.h>

int chdir(const char *path) {
  if (!path) {
    errno = EFAULT;
    return -1;
  }

  int16_t ret = Dsetpath(path);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return 0;
}
