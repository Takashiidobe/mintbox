#ifndef LIBC_SIGNAL_H
#define LIBC_SIGNAL_H

typedef void (*sighandler_t)(int);

#define SIGWINCH 28

#define SIG_DFL ((sighandler_t)0)
#define SIG_IGN ((sighandler_t)1)
#define SIG_ERR ((sighandler_t)-1)

sighandler_t signal(int sig, sighandler_t handler);

#endif /* LIBC_SIGNAL_H */
