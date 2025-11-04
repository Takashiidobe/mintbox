#ifndef LIBC_STDLIB_H
#define LIBC_STDLIB_H

#include <stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int atexit(void (*func)(void));
int atoi(const char *s);

#endif /* LIBC_STDLIB_H */
