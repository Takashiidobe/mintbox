#ifndef LIBC_STDIO_H
#define LIBC_STDIO_H

#include <stddef.h>

#define EOF (-1)

typedef struct __file FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int putchar(int c);
int putch(int c);
int puts(const char *s);
int remove(const char *path);

FILE *fopen(const char *path, const char *mode);
int fclose(FILE *stream);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
int fprintf(FILE *stream, const char *format, ...);
int fputs(const char *s, FILE *stream);

#endif /* LIBC_STDIO_H */
