#include <ctype.h>
#include <stddef.h>

#define CMDLINE_MAX 126
#define MAX_ARGS 16

static char argv_buffer[CMDLINE_MAX + 1];
static char *argv_vector[MAX_ARGS + 1];

int __libc_argc = 0;
char **__libc_argv = argv_vector;

void __libc_init_args(void *basepage) {
  unsigned char *cmd = (unsigned char *)basepage + 0x80;
  size_t len = cmd[0];

  if (len > CMDLINE_MAX)
    len = CMDLINE_MAX;

  size_t out = 0;
  for (; out < len; ++out) {
    char ch = (char)cmd[1 + out];
    if (ch == '\r')
      break;
    argv_buffer[out] = ch;
  }
  argv_buffer[out] = '\0';

  int argc = 0;
  argv_vector[argc++] = "";

  char *cursor = argv_buffer;
  while (*cursor && argc < MAX_ARGS) {
    while (*cursor && isspace((unsigned char)*cursor))
      ++cursor;
    if (!*cursor)
      break;

    argv_vector[argc++] = cursor;

    while (*cursor && !isspace((unsigned char)*cursor))
      ++cursor;
    if (!*cursor)
      break;

    *cursor++ = '\0';
  }

  argv_vector[argc] = NULL;
  __libc_argc = argc;
  __libc_argv = argv_vector;
}
