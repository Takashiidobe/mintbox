#include <errno.h>
#include <stddef.h>
#include <sys/random.h>

#define GETENTROPY_MAX 256

int getentropy(void *buf, size_t buflen) {
  if (buflen > GETENTROPY_MAX) {
    errno = EIO;
    return -1;
  }
  if (getrandom(buf, buflen, 0) < 0)
    return -1;
  return 0;
}
