#include <errno.h>
#include <mint/mintbind.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/random.h>

ssize_t getrandom(void *buf, size_t buflen, unsigned int flags) {
  if (!buf && buflen) {
    errno = EFAULT;
    return -1;
  }
  if (flags & ~(GRND_NONBLOCK | GRND_RANDOM)) {
    errno = EINVAL;
    return -1;
  }

  unsigned char *dst = buf;
  size_t remaining = buflen;

  while (remaining) {
    uint32_t value = (uint32_t)Random();
    size_t chunk = remaining < sizeof(value) ? remaining : sizeof(value);
    memcpy(dst, &value, chunk);
    dst += chunk;
    remaining -= chunk;
  }

  return (ssize_t)buflen;
}
