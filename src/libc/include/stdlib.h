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
__attribute__((__noreturn__)) void exit(int status);
char *utoa(char *dst, long value);
char *itoa(char *dst, long value);

char *getenv(const char *name);
int putenv(char *);
int clearenv(void);
int setenv(const char *name, const char *value, int overwrite);
int unsetenv(const char *name);
int getpid(void);
int kill(int pid, int sig);

void *memalign(size_t align, size_t len);
void abort(void);

#endif /* LIBC_STDLIB_H */
