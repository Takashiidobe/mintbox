#ifndef LIBC_STDIO_H
#define LIBC_STDIO_H

#include <stdarg.h>
#include <stddef.h>
#include <sys/types.h>

#define EOF (-1)

typedef struct __file FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int putchar(int c);
int putch(int c);
int puts(const char *s);
int remove(const char *path);
int fgetc(FILE *stream);
int ungetc(int c, FILE *stream);
int fflush(FILE *stream);

FILE *fopen(const char *path, const char *mode);
int fclose(FILE *stream);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
int fprintf(FILE *stream, const char *format, ...);
int vfprintf(FILE *stream, const char *format, va_list ap);
int printf(const char *format, ...);
int vprintf(const char *format, va_list ap);
int fputs(const char *s, FILE *stream);
void perror(const char *s);
int snprintf(char *str, size_t size, const char *format, ...);
int vsnprintf(char *str, size_t size, const char *format, va_list ap);
int sscanf(const char *str, const char *format, ...);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
int fcloseall(void);
int ferror(FILE *f);
int fputc(int c, FILE *f);
char *fgets(char *s, int n, FILE *fp);

#endif /* LIBC_STDIO_H */
