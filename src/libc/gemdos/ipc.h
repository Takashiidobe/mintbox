#ifndef GEMDOS_IPC_H
#define GEMDOS_IPC_H

#include "./syscall.h"
#include <stdint.h>

/* Forward declarations for SysV IPC structures. */
typedef struct msqid_ds msqid_ds;
typedef struct sembuf sembuf;
typedef struct shmid_ds shmid_ds;

// Pshmget - Obtain a shared memory segment identifier.
static inline int32_t Pshmget(int32_t key, int32_t size, int32_t shmflg) {
  return (int32_t)trap_1_wlll(0x170, (long)key, (long)size, (long)shmflg);
}

// Pshmctl - Control operations on a shared memory segment.
static inline int32_t Pshmctl(int32_t shmid, int32_t cmd, shmid_ds *buf) {
  return (int32_t)trap_1_wlll(0x171, (long)shmid, (long)cmd, (long)buf);
}

// Pshmat - Attach a shared memory segment.
static inline void *Pshmat(int32_t shmid, void *shmaddr, int32_t shmflg) {
  return (void *)trap_1_wlll(0x172, (long)shmid, (long)shmaddr, (long)shmflg);
}

// Pshmdt - Detach a shared memory segment.
static inline int32_t Pshmdt(void *shmaddr) {
  return (int32_t)trap_1_wl(0x173, (long)shmaddr);
}

// Psemget - Obtain a semaphore set identifier.
static inline int32_t Psemget(int32_t key, int32_t nsems, int32_t semflg) {
  return (int32_t)trap_1_wlll(0x174, (long)key, (long)nsems, (long)semflg);
}

// Psemctl - Control operations on a semaphore set.
static inline int32_t Psemctl(int32_t semid, int32_t semnum, int32_t cmd,
                              intptr_t arg) {
  return (int32_t)trap_1_wllll(0x175, (long)semid, (long)semnum, (long)cmd,
                               (long)arg);
}

// Psemop - Perform an array of semaphore operations.
static inline int32_t Psemop(int32_t semid, sembuf *sops, int32_t nsops) {
  return (int32_t)trap_1_wlll(0x176, (long)semid, (long)sops, (long)nsops);
}

// Psemconfig - Configure system-wide semaphore limits.
static inline int32_t Psemconfig(int32_t flag) {
  return (int32_t)trap_1_wl(0x177, (long)flag);
}

// Pmsgget - Obtain a message queue identifier.
static inline int32_t Pmsgget(int32_t key, int32_t msgflg) {
  return (int32_t)trap_1_wll(0x178, (long)key, (long)msgflg);
}

// Pmsgctl - Control operations on a message queue.
static inline int32_t Pmsgctl(int32_t msqid, int32_t cmd, msqid_ds *buf) {
  return (int32_t)trap_1_wlll(0x179, (long)msqid, (long)cmd, (long)buf);
}

// Pmsgsnd - Send a message to a queue.
static inline int32_t Pmsgsnd(int32_t msqid, const void *msgp, int32_t msgsz,
                              int32_t msgflg) {
  return (int32_t)trap_1_wllll(0x17A, (long)msqid, (long)msgp, (long)msgsz,
                               (long)msgflg);
}

// Pmsgrcv - Receive a message from a queue.
static inline int32_t Pmsgrcv(int32_t msqid, void *msgp, int32_t msgsz,
                              int32_t msgtyp, int32_t msgflg) {
  return (int32_t)trap_1_wlllll(0x17B, (long)msqid, (long)msgp, (long)msgsz,
                                (long)msgtyp, (long)msgflg);
}

#endif /* GEMDOS_IPC_H */
