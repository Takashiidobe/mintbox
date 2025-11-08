#include <errno.h>
#include <mint/mintbind.h>
#include <stdarg.h>
#include <stdint.h>
#include <sys/sem.h>

int semget(key_t key, int nsems, int semflg) {
  int32_t ret = Psemget((int32_t)key, (int32_t)nsems, (int32_t)semflg);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return (int)ret;
}

int semop(int semid, struct sembuf *sops, size_t nsops) {
  int32_t count = (int32_t)nsops;
  int32_t ret = Psemop((int32_t)semid, sops, count);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return 0;
}

int semctl(int semid, int semnum, int cmd, ...) {
  intptr_t arg = 0;
  va_list ap;
  va_start(ap, cmd);

  switch (cmd) {
  case SETVAL:
    arg = (intptr_t)va_arg(ap, int);
    break;
  case SETALL:
  case GETALL:
    arg = (intptr_t)va_arg(ap, unsigned short *);
    break;
  case IPC_SET:
  case IPC_STAT:
    arg = (intptr_t)va_arg(ap, struct semid_ds *);
    break;
  case IPC_INFO:
    arg = (intptr_t)va_arg(ap, void *);
    break;
  default:
    break;
  }

  va_end(ap);

  int32_t ret = Psemctl((int32_t)semid, (int32_t)semnum, (int32_t)cmd, arg);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return (int)ret;
}
