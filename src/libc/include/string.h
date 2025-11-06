#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#include <stddef.h>

void bcopy(const void *s1, void *s2, size_t n);
void bzero(void *s, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
size_t strlen(const char *s);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *dest, int c, size_t n);
char *strchr(const char *s, int c);
int memcmp(const void *s1, const void *s2, size_t n);
char *strstr(const char *haystack, const char *needle);
char *strerror(int errnum);
int strcmp(const char *s1, const char *s2);

#endif /* LIBC_STRING_H */
