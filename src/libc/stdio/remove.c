#include <errno.h>
#include <mint/mintbind.h>
#include <stdio.h>

int remove(const char *path) {
  int ret = Ddelete(path);
  if (ret == -ENOTDIR) {
    ret = Fdelete(path);
  }
  return ret < 0 ? -1 : 0;
}
