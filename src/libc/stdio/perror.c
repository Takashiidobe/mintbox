#include <errno.h>
#include <stdio.h>
#include <string.h>

void perror(const char *s) {
  const char *msg = strerror(errno);

  if (s && *s) {
    fprintf(stderr, "%s: %s\n", s, msg);
  } else {
    fprintf(stderr, "%s\n", msg);
  }
}
