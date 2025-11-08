#ifndef LIBC_UNISTD_H
#define LIBC_UNISTD_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define F_OK 0
#define X_OK 1
#define W_OK 2
#define R_OK 4

ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int close(int fd);
int isatty(int fd);
int ftruncate(int fd, off_t length);
void *sbrk(intptr_t increment);
off_t lseek(int fd, off_t offset, int whence);
int dup(int fd);
int dup2(int oldfd, int newfd);
int pipe(int pipefd[2]);
int unlink(const char *path);
int link(const char *oldpath, const char *newpath);
int mkdir(const char *path, mode_t mode);
int rmdir(const char *path);
int chdir(const char *path);
char *getcwd(char *buf, size_t size);
int access(const char *path, int mode);
uid_t getuid(void);
uid_t geteuid(void);
gid_t getgid(void);
gid_t getegid(void);
int getgroups(int gidsetsize, gid_t grouplist[]);

#endif /* LIBC_UNISTD_H */
