#include <errno.h>
#include <mint/mintbind.h>
#include <stdint.h>
#include <sys/shm.h>

int shmget(key_t key, size_t size, int shmflg) {
  int32_t ret = Pshmget((int32_t)key, (int32_t)size, (int32_t)shmflg);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return (int)ret;
}

int shmctl(int shmid, int cmd, struct shmid_ds *buf) {
  int32_t ret = Pshmctl((int32_t)shmid, (int32_t)cmd, buf);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return (int)ret;
}

void *shmat(int shmid, const void *shmaddr, int shmflg) {
  void *ptr = Pshmat((int32_t)shmid, (void *)shmaddr, (int32_t)shmflg);
  if ((intptr_t)ptr < 0) {
    errno = (int)-(intptr_t)ptr;
    return (void *)-1;
  }
  return ptr;
}

int shmdt(const void *shmaddr) {
  int32_t ret = Pshmdt((void *)shmaddr);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return 0;
}
