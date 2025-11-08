#include <errno.h>
#include <mint/mintbind.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t wait(int *status) {
  return waitpid(-1, status, 0);
}

pid_t waitpid(pid_t pid, int *status, int options) {
  if (options & ~(WNOHANG | WUNTRACED)) {
    errno = EINVAL;
    return -1;
  }

  int16_t target = (pid == -1) ? (int16_t)-1 : (int16_t)pid;
  int32_t ret = Pwaitpid(target, (int16_t)options, NULL);
  if (ret == 0 && (options & WNOHANG)) {
    if (status)
      *status = 0;
    return 0;
  }
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }

  uint32_t uret = (uint32_t)ret;
  pid_t child = (pid_t)(uret >> 16);
  int raw_status = (int)(uret & 0xFFFF);
  if (status)
    *status = raw_status;
  return child;
}
