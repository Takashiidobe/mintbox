#ifndef LIBC_STDLIB_H
#define LIBC_STDLIB_H

#include <stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int atexit(void (*fn)(void));
int atoi(const char *s);
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t count, size_t size);
void exit(int status);
char *utoa(char *dst, long value);
char *itoa(char *dst, long value);

#endif /* LIBC_STDLIB_H */
