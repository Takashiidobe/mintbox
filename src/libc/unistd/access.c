#include <errno.h>
#include <mint/mintbind.h>
#include <mint/xattr.h>
#include <stdint.h>
#include <sys/param.h>
#include <sys/types.h>
#include <unistd.h>

static unsigned int mode_mask(int mode) {
  unsigned int mask = 0;
  if (mode & R_OK)
    mask |= 4;
  if (mode & W_OK)
    mask |= 2;
  if (mode & X_OK)
    mask |= 1;
  return mask;
}

int access(const char *path, int mode) {
  if (!path) {
    errno = EFAULT;
    return -1;
  }

  XATTR attr;
  int32_t ret = Fxattr(0, (char *)path, &attr);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }

  unsigned int request = mode & (R_OK | W_OK | X_OK);
  if (request == 0)
    return 0;

  uid_t uid = getuid();
  if (uid == 0)
    return 0;

  unsigned int mask = mode_mask(request);

  if ((uid_t)attr.st_uid == uid) {
    if (((attr.st_mode >> 6) & mask) == mask)
      return 0;
    errno = EACCES;
    return -1;
  }

  gid_t gid = getgid();
  if ((gid_t)attr.st_gid == gid) {
    if (((attr.st_mode >> 3) & mask) == mask)
      return 0;
  } else {
    gid_t groups[NGROUPS_MAX];
    int n = getgroups(NGROUPS_MAX, groups);
    if (n > 0) {
      for (int i = 0; i < n; ++i) {
        if (groups[i] == (gid_t)attr.st_gid) {
          if (((attr.st_mode >> 3) & mask) == mask)
            return 0;
          errno = EACCES;
          return -1;
        }
      }
    }
  }

  if ((attr.st_mode & mask) == mask)
    return 0;

  errno = EACCES;
  return -1;
}
