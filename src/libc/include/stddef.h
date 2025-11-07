#ifndef LIBC_STDDEF_H
#define LIBC_STDDEF_H

#ifndef __LIBC_SIZE_T_DEFINED
#define __LIBC_SIZE_T_DEFINED
typedef unsigned long size_t;
#endif

#ifndef __LIBC_SSIZE_T_DEFINED
#define __LIBC_SSIZE_T_DEFINED
typedef long ssize_t;
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#endif /* LIBC_STDDEF_H */
