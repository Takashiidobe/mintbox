#include <errno.h>
#include <mint/mintbind.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define CMDLINE_MAX 125 /* GEMDOS command line max payload length */

static void build_cmdline(char *buf, char *const argv[]) {
  size_t len = 0;
  buf[0] = 0;

  if (!argv)
    goto done;

  for (int i = 1; argv[i]; ++i) {
    if (len >= CMDLINE_MAX)
      break;
    if (len && len < CMDLINE_MAX)
      buf[1 + len++] = ' ';

    const char *arg = argv[i];
    while (*arg && len < CMDLINE_MAX) {
      buf[1 + len++] = *arg++;
    }
  }

done:
  buf[0] = (char)len;
  buf[1 + len] = '\r';
}

static char *build_env(char *const envp[]) {
  size_t total = 1; /* final null */
  if (envp) {
    for (int i = 0; envp[i]; ++i)
      total += strlen(envp[i]) + 1;
  }

  char *block = malloc(total);
  if (!block)
    return NULL;

  char *p = block;
  if (envp) {
    for (int i = 0; envp[i]; ++i) {
      size_t len = strlen(envp[i]);
      memcpy(p, envp[i], len);
      p += len;
      *p++ = '\0';
    }
  }
  *p = '\0';
  return block;
}

int execve(const char *path, char *const argv[], char *const envp[]) {
  if (!path) {
    errno = EFAULT;
    return -1;
  }

  char cmdline[CMDLINE_MAX + 2];
  build_cmdline(cmdline, argv);

  char *env_block = build_env(envp);
  if (!env_block) {
    errno = ENOMEM;
    return -1;
  }

  int32_t ret = Pexec(0, (const int8_t *)path, cmdline, env_block);
  free(env_block);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }

  errno = ENOSYS;
  return -1;
}
