#ifndef LIBC_SYS_TIME_H
#define LIBC_SYS_TIME_H

#include <sys/types.h>

struct timeval {
  __time_t tv_sec;       /* Seconds. */
  __suseconds_t tv_usec; /* Microseconds. */
};

struct timezone {
  int tz_minuteswest; /* Minutes west of GMT. */
  int tz_dsttime;     /* Nonzero if DST is ever in effect. */
};

int gettimeofday(struct timeval *tv, struct timezone *tz);

#endif /* LIBC_SYS_TIME_H */
