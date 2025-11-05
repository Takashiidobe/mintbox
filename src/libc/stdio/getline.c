#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_BUFFER_SIZE 128

ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
  if (!lineptr || !n || !stream)
    return -1;

  if (*lineptr == NULL || *n == 0) {
    *n = INITIAL_BUFFER_SIZE;
    *lineptr = (char *)malloc(*n);
    if (!*lineptr) {
      errno = ENOMEM;
      return -1;
    }
  }

  size_t pos = 0;
  while (1) {
    char ch;
    size_t read = fread(&ch, 1, 1, stream);
    if (read == 0) {
      if (pos == 0)
        return -1;
      break;
    }

    if (pos + 1 >= *n) {
      size_t new_size = (*n) * 2;
      char *new_buf = (char *)realloc(*lineptr, new_size);
      if (!new_buf) {
        errno = ENOMEM;
        return -1;
      }
      *lineptr = new_buf;
      *n = new_size;
    }

    (*lineptr)[pos++] = ch;
    if (ch == '\n')
      break;
  }

  (*lineptr)[pos] = '\0';
  return (ssize_t)pos;
}
