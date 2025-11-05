#include "./gemdos/file.h"
#include <unistd.h>

#define FTRUNCATE (('F' << 8) | 4)

int ftruncate(int fd, off_t length) {
  long r = Fcntl(fd, &length, FTRUNCATE);
  return r;
}
