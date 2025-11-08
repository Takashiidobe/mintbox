#ifndef LIBC_SYS_SEM_H
#define LIBC_SYS_SEM_H

#include <sys/ipc.h>
#include <sys/types.h>

struct sembuf {
  unsigned short sem_num;
  short sem_op;
  short sem_flg;
};

struct semid_ds {
  struct ipc_perm sem_perm;
  unsigned long __unused1;
  unsigned short sem_nsems;
  time_t sem_otime;
  unsigned long __unused2;
  time_t sem_ctime;
  unsigned long __unused3;
  unsigned long __unused4[4];
};

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  void *__pad;
};

#define SEM_UNDO 0x1000

#define GETPID 11
#define GETVAL 12
#define GETALL 13
#define GETNCNT 14
#define GETZCNT 15
#define SETVAL 16
#define SETALL 17

int semget(key_t key, int nsems, int semflg);
int semop(int semid, struct sembuf *sops, size_t nsops);
int semctl(int semid, int semnum, int cmd, ...);

#endif /* LIBC_SYS_SEM_H */
