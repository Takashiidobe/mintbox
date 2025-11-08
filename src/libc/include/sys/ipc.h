#ifndef LIBC_SYS_IPC_H
#define LIBC_SYS_IPC_H

#include <sys/types.h>

struct ipc_perm {
  uid_t uid;
  gid_t gid;
  uid_t cuid;
  gid_t cgid;
  mode_t mode;
};

#define IPC_CREAT 01000
#define IPC_EXCL 02000
#define IPC_NOWAIT 04000

#define IPC_RMID 0
#define IPC_SET 1
#define IPC_STAT 2
#define IPC_INFO 3

#define IPC_PRIVATE ((key_t)0)

key_t ftok(const char *pathname, int proj_id);

#endif /* LIBC_SYS_IPC_H */
