#include <errno.h>
#include <mint/mintbind.h>
#include <sys/types.h>
#include <unistd.h>

pid_t fork(void) {
  long ret = Pfork();
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return (pid_t)ret;
}
