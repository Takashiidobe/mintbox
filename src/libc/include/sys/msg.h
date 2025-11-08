#ifndef LIBC_SYS_MSG_H
#define LIBC_SYS_MSG_H

#include <sys/ipc.h>
#include <sys/types.h>

#define MSG_NOERROR 010000
#define MSG_EXCEPT 020000

struct msqid_ds {
  struct ipc_perm msg_perm;
  time_t msg_stime;
  time_t msg_rtime;
  time_t msg_ctime;
  unsigned long msg_cbytes;
  msgqnum_t msg_qnum;
  msglen_t msg_qbytes;
  pid_t msg_lspid;
  pid_t msg_lrpid;
  unsigned long __unused[2];
};

struct msgbuf {
  long mtype;
  char mtext[1];
};

int msgget(key_t key, int msgflg);
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);

#endif /* LIBC_SYS_MSG_H */
