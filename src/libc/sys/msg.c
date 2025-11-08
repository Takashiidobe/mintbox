#include <errno.h>
#include <limits.h>
#include <mint/mintbind.h>
#include <stdint.h>
#include <sys/msg.h>

int msgget(key_t key, int msgflg) {
  int32_t ret = Pmsgget((int32_t)key, (int32_t)msgflg);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return (int)ret;
}

int msgctl(int msqid, int cmd, struct msqid_ds *buf) {
  int32_t ret = Pmsgctl((int32_t)msqid, (int32_t)cmd, buf);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return (int)ret;
}

int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg) {
  if (msgsz > (size_t)INT32_MAX) {
    errno = EINVAL;
    return -1;
  }
  int32_t ret =
      Pmsgsnd((int32_t)msqid, msgp, (int32_t)msgsz, (int32_t)msgflg);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return 0;
}

ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg) {
  if (msgsz > (size_t)INT32_MAX) {
    errno = EINVAL;
    return -1;
  }
  int32_t ret = Pmsgrcv((int32_t)msqid, msgp, (int32_t)msgsz, (int32_t)msgtyp,
                        (int32_t)msgflg);
  if (ret < 0) {
    errno = (int)-ret;
    return -1;
  }
  return (ssize_t)ret;
}
