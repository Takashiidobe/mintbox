#ifndef LIBC_UNISTD_H
#define LIBC_UNISTD_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#ifndef _POSIX_VERSION
#define _POSIX_VERSION 199009L
#endif

#ifndef __POSIX2_THIS_VERSION
#define __POSIX2_THIS_VERSION 199209L
#endif

#ifndef _POSIX2_VERSION
#define _POSIX2_VERSION __POSIX2_THIS_VERSION
#endif

#ifndef _POSIX2_C_VERSION
#define _POSIX2_C_VERSION __POSIX2_THIS_VERSION
#endif

#ifndef _POSIX2_C_BIND
#define _POSIX2_C_BIND __POSIX2_THIS_VERSION
#endif

#ifndef _POSIX2_C_DEV
#define _POSIX2_C_DEV __POSIX2_THIS_VERSION
#endif

#ifndef _POSIX2_SW_DEV
#define _POSIX2_SW_DEV __POSIX2_THIS_VERSION
#endif

#ifndef _POSIX2_LOCALEDEF
#define _POSIX2_LOCALEDEF __POSIX2_THIS_VERSION
#endif

#ifndef _XOPEN_VERSION
#define _XOPEN_VERSION 4
#endif

#ifndef _XOPEN_XCU_VERSION
#define _XOPEN_XCU_VERSION 4
#endif

#ifndef _XOPEN_XPG2
#define _XOPEN_XPG2 1
#endif

#ifndef _XOPEN_XPG3
#define _XOPEN_XPG3 1
#endif

#ifndef _XOPEN_XPG4
#define _XOPEN_XPG4 1
#endif

#ifndef _XOPEN_UNIX
#define _XOPEN_UNIX 1
#endif

#ifndef _XOPEN_CRYPT
#define _XOPEN_CRYPT 1
#endif

#ifndef _XOPEN_ENH_I18N
#define _XOPEN_ENH_I18N 1
#endif

#ifndef _XOPEN_LEGACY
#define _XOPEN_LEGACY 1
#endif

#ifndef _POSIX_JOB_CONTROL
#define _POSIX_JOB_CONTROL 1
#endif

#ifndef _POSIX_SAVED_IDS
#define _POSIX_SAVED_IDS 1
#endif

#ifndef _POSIX_SYNCHRONIZED_IO
#define _POSIX_SYNCHRONIZED_IO 1
#endif

#ifndef _POSIX_FSYNC
#define _POSIX_FSYNC 1
#endif

#ifndef _POSIX_SELECT
#define _POSIX_SELECT 1
#endif

#ifndef _POSIX_CHOWN_RESTRICTED
#define _POSIX_CHOWN_RESTRICTED 1
#endif

#ifndef _POSIX_VDISABLE
#define _POSIX_VDISABLE '\0'
#endif

#ifndef _POSIX_NO_TRUNC
#define _POSIX_NO_TRUNC 1
#endif

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
pid_t getppid(void);
int access(const char *path, int mode);
uid_t getuid(void);
uid_t geteuid(void);
gid_t getgid(void);
gid_t getegid(void);
int getgroups(int gidsetsize, gid_t grouplist[]);
pid_t fork(void);
int execve(const char *path, char *const argv[], char *const envp[]);

#endif /* LIBC_UNISTD_H */
