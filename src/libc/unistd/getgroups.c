#include <errno.h>
#include <mint/mintbind.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int getgroups(int gidsetsize, gid_t grouplist[]) {
  if (gidsetsize < 0) {
    errno = EINVAL;
    return -1;
  }
  if (gidsetsize > 0 && !grouplist) {
    errno = EFAULT;
    return -1;
  }

  int16_t *tmp = NULL;
  if (gidsetsize > 0) {
    tmp = malloc((size_t)gidsetsize * sizeof(int16_t));
    if (!tmp) {
      errno = ENOMEM;
      return -1;
    }
  }

  int32_t ret = Pgetgroups((int16_t)gidsetsize, tmp);
  if (ret < 0) {
    free(tmp);
    errno = (int)-ret;
    return -1;
  }

  if (tmp && grouplist) {
    int count = ret < gidsetsize ? ret : gidsetsize;
    for (int i = 0; i < count; ++i)
      grouplist[i] = (gid_t)tmp[i];
  }

  free(tmp);
  return (int)ret;
}
