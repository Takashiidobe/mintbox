#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#include <stddef.h>

void bcopy(const void *s1, void *s2, size_t n);
void bzero(void *s, size_t n);
void *memchr(const void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *dest, int c, size_t n);
size_t strnlen(const char *s, size_t maxlen);
size_t strlen(const char *s);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
char *strdup(const char *s);
char *strchr(const char *s, int c);
char *strstr(const char *haystack, const char *needle);
char *strerror(int errnum);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
void swab(const void *src, void *dst, ssize_t n);

#endif /* LIBC_STRING_H */
