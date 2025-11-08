#ifndef LIBC_SYS_SHM_H
#define LIBC_SYS_SHM_H

#include <sys/ipc.h>
#include <sys/types.h>

#define SHM_RDONLY 010000
#define SHM_RND 020000
#define SHM_REMAP 040000

#define SHM_LOCK 11
#define SHM_UNLOCK 12

struct shmid_ds {
  struct ipc_perm shm_perm;
  int shm_segsz;
  time_t shm_atime;
  time_t shm_dtime;
  time_t shm_ctime;
  pid_t shm_cpid;
  pid_t shm_lpid;
  shmatt_t shm_nattch;
};

void *shmat(int shmid, const void *shmaddr, int shmflg);
int shmdt(const void *shmaddr);
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
int shmget(key_t key, size_t size, int shmflg);

#endif /* LIBC_SYS_SHM_H */
