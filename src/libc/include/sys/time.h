#ifndef LIBC_SYS_TIME_H
#define LIBC_SYS_TIME_H

#include <stdint.h>

#ifndef __LIBC_TIME_T_DEFINED
#define __LIBC_TIME_T_DEFINED
typedef int32_t time_t;
typedef time_t __time_t;
#endif

#ifndef __LIBC_SUSECONDS_T_DEFINED
#define __LIBC_SUSECONDS_T_DEFINED
typedef int32_t suseconds_t;
typedef suseconds_t __suseconds_t;
#endif

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
