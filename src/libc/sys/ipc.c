#include <errno.h>
#include <mint/mintbind.h>
#include <mint/xattr.h>
#include <stdint.h>
#include <sys/ipc.h>
#include <sys/types.h>

key_t ftok(const char *pathname, int proj_id) {
  if (!pathname || proj_id == 0) {
    errno = EINVAL;
    return (key_t)-1;
  }

  XATTR attr;
  int32_t ret = Fxattr(0, (char *)pathname, &attr);
  if (ret < 0) {
    errno = (int)-ret;
    return (key_t)-1;
  }

  return (key_t)((attr.st_ino & 0xFFFF) | ((attr.st_dev & 0xFF) << 16) |
                 ((proj_id & 0xFF) << 24));
}
