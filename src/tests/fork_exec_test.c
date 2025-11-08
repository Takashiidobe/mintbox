#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static void exercise_exec(void) {
  char *const args[] = {"ls", "-1", NULL};
  char *const envp[] = {"LC_ALL=C", NULL};

  execve("/bin/ls", args, envp);
  perror("execve(/bin/ls)");
  exit(127);
}

int main(void) {
  printf("parent pid=%d\n", getpid());

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return 1;
  }

  if (pid == 0) {
    printf("child pid=%d, parent pid=%d\n", getpid(), getppid());
    fflush(stdout);
    exercise_exec();
  }

  printf("spawned child %d\n", pid);

  int status;
  if (waitpid(pid, &status, 0) < 0) {
    perror("waitpid");
    return 1;
  }

  if (WIFEXITED(status)) {
    printf("child exited with %d\n", WEXITSTATUS(status));
  } else if (WIFSIGNALED(status)) {
    printf("child killed by signal %d\n", WTERMSIG(status));
  } else {
    printf("child stopped (status=%d)\n", status);
  }

  return 0;
}
