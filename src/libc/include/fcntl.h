#ifndef LIBC_FCNTL_H
#define LIBC_FCNTL_H

#include <stdint.h>

#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2
#define O_CREAT 0x0200
#define O_TRUNC 0x0400

int open(const char *path, int flags, ...);

#endif /* LIBC_FCNTL_H */
