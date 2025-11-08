#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <unistd.h>

static unsigned char random_byte(void) {
  unsigned char byte;
  if (getrandom(&byte, sizeof(byte), GRND_NONBLOCK) >= 0)
    return byte;
  return (unsigned char)rand();
}

static char random_char(void) {
  static const char alphabet[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  return alphabet[random_byte() % (sizeof(alphabet) - 1)];
}

char *mktemp(char *template) {
  if (!template) {
    errno = EINVAL;
    return NULL;
  }

  size_t len = strlen(template);
  if (len < 6 || strcmp(template + len - 6, "XXXXXX") != 0) {
    errno = EINVAL;
    template[0] = '\0';
    return template;
  }

  char *xs = template + len - 6;

  for (int attempt = 0; attempt < 50; attempt++) {
    for (int i = 0; i < 6; i++) {
      xs[i] = random_char();
    }

    if (access(template, F_OK) != 0) {
      if (errno == ENOENT)
        return template;
    } else {
      continue;
    }
  }

  template[0] = '\0';
  errno = EEXIST;
  return template;
}
