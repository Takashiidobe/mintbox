#include <errno.h>
#include <mint/mintbind.h>
#include <stdint.h>
#include <unistd.h>

int unlink(const char *path) {
  if (!path) {
    errno = EFAULT;
    return -1;
  }

  int32_t ret = Fdelete(path);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return 0;
}
