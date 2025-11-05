#ifndef LIBC_FCNTL_H
#define LIBC_FCNTL_H

#include <stdint.h>

#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2
#define O_ACCMODE 0x0003

#define O_APPEND 0x0008
#define O_NONBLOCK 0x0010

#define O_CREAT 0x0200
#define O_TRUNC 0x0400
#define O_EXCL 0x0800
#define O_NOCTTY 0x1000
#define O_SYNC 0x2000

int open(const char *path, int flags, ...);

#endif /* LIBC_FCNTL_H */
