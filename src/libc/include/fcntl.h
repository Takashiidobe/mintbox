#ifndef LIBC_FCNTL_H
#define LIBC_FCNTL_H

#include <stdint.h>
#include <sys/types.h>

#define O_RDONLY 0x0000
#define O_WRONLY 0x0001
#define O_RDWR 0x0002
#define O_ACCMODE (O_RDONLY | O_WRONLY | O_RDWR)

#define O_CREAT 0x0200
#define O_TRUNC 0x0400
#define O_EXCL 0x0800
#define O_APPEND 0x1000
#define _REALO_APPEND 0x0008
#define O_NONBLOCK 0x0100
#define O_NDELAY O_NONBLOCK
#define O_NOCTTY 0x4000
#define O_NOATIME 0x0004
#define O_DIRECTORY 0x10000
#define O_NOFOLLOW 0x20000

#define O_COMPAT 0x0000
#define O_DENYRW 0x0010
#define O_DENYW 0x0020
#define O_DENYR 0x0030
#define O_DENYNONE 0x0040
#define O_SHMODE 0x0070
#define O_SYNC 0x0000

#define F_DUPFD 0
#define F_GETFD 1
#define F_SETFD 2
#define F_GETFL 3
#define F_SETFL 4
#define F_GETLK 5
#define F_SETLK 6
#define F_SETLKW 7
#define F_GETOWN 8
#define F_SETOWN 9

#define FD_CLOEXEC 1
#define F_DUPFD_CLOEXEC 1030

struct flock {
  short l_type;
  short l_whence;
  long l_start;
  long l_len;
  short l_pid;
};

#define F_RDLCK O_RDONLY
#define F_WRLCK O_WRONLY
#define F_UNLCK 3

#define POSIX_FADV_NORMAL 0
#define POSIX_FADV_RANDOM 1
#define POSIX_FADV_SEQUENTIAL 2
#define POSIX_FADV_WILLNEED 3
#define POSIX_FADV_DONTNEED 4
#define POSIX_FADV_NOREUSE 5

#define F_ULOCK 0
#define F_LOCK 1
#define F_TLOCK 2
#define F_TEST 3

int open(const char *path, int flags, ...);
int creat(const char *path, mode_t mode);
int fcntl(int fd, int cmd, ...);

#endif /* LIBC_FCNTL_H */
