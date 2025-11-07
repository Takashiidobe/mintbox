#include <mint/mintbind.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count) {
  if (count > (size_t)INT32_MAX) {
    errno = EINVAL;
    return -1;
  }
  if (fd != 1 && fd != 2) {

    int32_t ret = Fwrite((int16_t)fd, (int32_t)count, buf);
    if (ret < 0) {
      errno = (int)-ret;
      return -1;
    }
    return (ssize_t)ret;
  } else {
    // force "\r\n" on all writers when they just write an '\n'
    long total = 0;
    const unsigned char *p = buf;
    while (count) {
      const unsigned char *q = p;
      while (q < p + count && *q != '\n')
        q++;
      long chunk = (long)(q - p);
      if (chunk) {
        long r = Fwrite((short)fd, chunk, p);
        if (r <= 0)
          return total ? total : r;
        total += r;
      }
      if (q < p + count) {
        long r = Fwrite((short)fd, 2, "\r\n");
        if (r <= 0)
          return total ? total : r;
        total += r;
        p = q + 1;
        count -= (unsigned long)(chunk + 1);
      } else {
        break;
      }
    }
    return total;
  }
}
