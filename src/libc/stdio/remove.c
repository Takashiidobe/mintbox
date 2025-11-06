#include "../gemdos/directory.h"
#include "../gemdos/file.h"
#include <errno.h>
#include <stdio.h>

int remove(const char *path) {
  int ret = Ddelete(path);
  if (ret == -ENOTDIR) {
    ret = Fdelete(path);
  }
  return ret < 0 ? -1 : 0;
}
