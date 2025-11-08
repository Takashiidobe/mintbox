#ifndef LIBC_SYS_WAIT_H
#define LIBC_SYS_WAIT_H

#include <sys/types.h>

#define WNOHANG 1
#define WUNTRACED 2

#define __WSTATUS(status) ((status)&0xFFFF)
#define __WTERMSIG(status) (__WSTATUS(status) & 0x7F)
#define __WCOREDUMP(status) (__WSTATUS(status) & 0x80)
#define __WEXITSTATUS(status) (((status) >> 8) & 0xFF)

#define WIFEXITED(status) (__WTERMSIG(status) == 0)
#define WEXITSTATUS(status) __WEXITSTATUS(status)
#define WIFSIGNALED(status)                                                     \
  (__WTERMSIG(status) != 0 && __WTERMSIG(status) != 0x7F)
#define WTERMSIG(status) __WTERMSIG(status)
#define WCOREDUMP(status) (__WCOREDUMP(status) != 0)
#define WIFSTOPPED(status) (__WTERMSIG(status) == 0x7F)
#define WSTOPSIG(status) __WEXITSTATUS(status)

pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);

#endif /* LIBC_SYS_WAIT_H */
