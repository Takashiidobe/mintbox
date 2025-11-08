#ifndef MINT_XATTR_H
#define MINT_XATTR_H

#include <sys/types.h>

typedef struct XATTR {
  unsigned short st_mode;
  long st_ino;
  unsigned short st_dev;
  short st_rdev;
  unsigned short st_nlink;
  unsigned short st_uid;
  unsigned short st_gid;
  long st_size;
  long st_blksize;
  long st_blocks;
  unsigned long st_mtime;
  unsigned long st_atime;
  unsigned long st_ctime;
  short st_attr;
  short res1;
  long res2[2];
} XATTR;

#endif /* MINT_XATTR_H */
