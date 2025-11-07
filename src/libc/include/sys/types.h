#ifndef LIBC_SYS_TYPES_H
#define LIBC_SYS_TYPES_H

#include <stddef.h>
#include <stdint.h>

typedef unsigned long __mode_t;

#ifndef __LIBC_OFF_T_DEFINED
#define __LIBC_OFF_T_DEFINED
typedef long off_t;
#endif

#ifndef __LIBC_PID_T_DEFINED
#define __LIBC_PID_T_DEFINED
typedef int pid_t;
#endif

#ifndef __LIBC_UID_T_DEFINED
#define __LIBC_UID_T_DEFINED
typedef int uid_t;
typedef int gid_t;
#endif

#ifndef __LIBC_SIZE_T_DEFINED
#define __LIBC_SIZE_T_DEFINED
typedef unsigned long size_t;
#endif

#ifndef __LIBC_SSIZE_T_DEFINED
#define __LIBC_SSIZE_T_DEFINED
typedef long ssize_t;
#endif

#ifndef __LIBC_TIME_T_DEFINED
#define __LIBC_TIME_T_DEFINED
typedef long time_t;
typedef time_t __time_t;
#endif

#ifndef __MODE_T_DEFINED
#define __MODE_T_DEFINED
typedef __mode_t mode_t;
#endif

#ifndef __LIBC_SUSECONDS_T_DEFINED
#define __LIBC_SUSECONDS_T_DEFINED
typedef long suseconds_t;
typedef suseconds_t __suseconds_t;
#endif

typedef long clock_t;

#endif /* LIBC_SYS_TYPES_H */
