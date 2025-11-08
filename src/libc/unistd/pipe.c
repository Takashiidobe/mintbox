#include <errno.h>
#include <mint/mintbind.h>
#include <stdint.h>
#include <unistd.h>

int pipe(int pipefd[2]) {
  if (!pipefd) {
    errno = EINVAL;
    return -1;
  }

  int16_t handles[2];
  int32_t ret = Fpipe(handles);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }

  pipefd[0] = handles[0];
  pipefd[1] = handles[1];
  return 0;
}
