#ifndef LIBC_STDIO_INTERNAL_H
#define LIBC_STDIO_INTERNAL_H

#include <stdio.h>

#define FILE_FLAG_INUSE 0x01
#define FILE_FLAG_STATIC 0x02

struct __file {
  int handle;
  unsigned char flags;
};

FILE *__stdio_alloc_file(void);
void __stdio_release_file(FILE *file);
FILE *__stdio_file_pool(void);
int __stdio_file_pool_size(void);

#endif /* LIBC_STDIO_INTERNAL_H */
