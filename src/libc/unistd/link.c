#include <errno.h>
#include <mint/mintbind.h>
#include <stdint.h>
#include <unistd.h>

int link(const char *oldpath, const char *newpath) {
  if (!oldpath || !newpath) {
    errno = EFAULT;
    return -1;
  }

  int32_t ret = Flink((char *)oldpath, (int8_t *)newpath);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return 0;
}
