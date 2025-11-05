#include "./gemdos/file.h"
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdint.h>

int open(const char *path, int flags, ...) {
  if (!path) {
    errno = EINVAL;
    return -1;
  }

  int create_mode = 0;
  if (flags & O_CREAT) {
    va_list ap;
    va_start(ap, flags);
    create_mode = va_arg(ap, int);
    (void)create_mode;
    va_end(ap);
  }

  int16_t access = 0;
  if ((flags & O_RDWR) == O_RDWR) {
    access = 2;
  } else if ((flags & O_WRONLY) == O_WRONLY) {
    access = 1;
  } else {
    access = 0;
  }

  if (flags & (O_CREAT | O_TRUNC)) {
    int32_t create_handle = Fcreate((const int8_t *)path, 0);
    if (create_handle < 0) {
      errno = (int)-create_handle;
      return -1;
    }
    Fclose((int16_t)create_handle);
  }

  int32_t handle = Fopen((const int8_t *)path, access);
  if (handle < 0) {
    errno = (int)-handle;
    return -1;
  }
  return (int)handle;
}
