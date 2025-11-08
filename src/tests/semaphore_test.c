#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
  if (semid < 0) {
    perror("semget");
    return 1;
  }

  union semun arg;
  arg.val = 0;
  if (semctl(semid, 0, SETVAL, arg) < 0) {
    perror("semctl SETVAL");
    semctl(semid, 0, IPC_RMID);
    return 1;
  }

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    semctl(semid, 0, IPC_RMID);
    return 1;
  }

  if (pid == 0) {
    struct sembuf down = {0, -1, 0};
    if (semop(semid, &down, 1) < 0) {
      perror("child semop -1");
      exit(2);
    }
    int val = semctl(semid, 0, GETVAL);
    if (val < 0) {
      perror("child GETVAL");
      exit(3);
    }
    printf("child pid=%d acquired semaphore (value now %d)\n", getpid(), val);
    exit(val == 0 ? 0 : 4);
  }

  struct sembuf up = {0, 1, 0};
  if (semop(semid, &up, 1) < 0) {
    perror("parent semop +1");
    semctl(semid, 0, IPC_RMID);
    return 1;
  }
  printf("parent pid=%d released semaphore for child %d\n", getpid(), pid);

  int status;
  if (waitpid(pid, &status, 0) < 0) {
    perror("waitpid");
    semctl(semid, 0, IPC_RMID);
    return 1;
  }

  int rc = 0;
  if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
    fprintf(stderr, "child exited abnormally (status=%d)\n", status);
    rc = 1;
  } else {
    puts("semaphore handoff succeeded");
  }

  if (semctl(semid, 0, IPC_RMID) < 0)
    perror("semctl IPC_RMID");

  return rc;
}
