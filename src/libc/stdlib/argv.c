#include <stddef.h>
#include <stdint.h>

#include <mint/basepage.h>

extern int main(int argc, char **argv, char **envp);

static char *default_argv[] = {"", NULL};

int __libc_argc = 1;
char **__libc_argv = default_argv;
char **environ = NULL;
BASEPAGE *_base asm("_base");

static uint8_t *align4(uint8_t *ptr) {
  uintptr_t value = (uintptr_t)ptr;
  value = (value + 3U) & ~((uintptr_t)3U);
  return (uint8_t *)value;
}

static void init_environ(const BASEPAGE *bp, uint8_t **arena) {
  char **dst = (char **)*arena;
  environ = dst;

  char *entry = bp->p_env;
  if (entry) {
    while (*entry) {
      *dst++ = entry;
      while (*entry++)
        ;
    }
  }

  *dst++ = NULL;
  *arena = align4((uint8_t *)dst);
}

static char *copy_command_line(const BASEPAGE *bp, uint8_t **arena) {
  unsigned length = bp->p_cmdlin[0];
  if (length > 126)
    length = 126;

  char *buffer = (char *)*arena;
  for (unsigned i = 0; i < length; ++i) {
    char ch = (char)bp->p_cmdlin[1 + i];
    if (ch == '\r') {
      length = i;
      break;
    }
    buffer[i] = ch;
  }

  buffer[length++] = '\0';
  buffer[length] = '\0';
  *arena = align4((uint8_t *)(buffer + length + 1));

  return buffer;
}

static void init_args(char *cmdline, uint8_t **arena) {
  char **argv = (char **)*arena;
  __libc_argv = argv;

  int argc = 0;
  argv[argc++] = "";

  char *cursor = cmdline;
  while (*cursor) {
    while (*cursor == ' ' || *cursor == '\t')
      ++cursor;
    if (!*cursor)
      break;

    argv[argc++] = cursor;

    while (*cursor && *cursor != ' ' && *cursor != '\t')
      ++cursor;
    if (*cursor)
      *cursor++ = '\0';
  }

  argv[argc] = NULL;
  __libc_argc = argc;
  *arena = align4((uint8_t *)(argv + argc + 1));
}

int __libc_start_main(BASEPAGE *bp) {
  _base = bp;

  uint8_t *arena = align4((uint8_t *)bp->p_bbase + bp->p_blen);
  init_environ(bp, &arena);
  char *cmdline = copy_command_line(bp, &arena);
  init_args(cmdline, &arena);

  return main(__libc_argc, __libc_argv, environ);
}
