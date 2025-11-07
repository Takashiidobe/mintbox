#include <mint/mintbind.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>

int close(int fd) {
  int32_t ret = Fclose((int16_t)fd);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return 0;
}
