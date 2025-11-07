#ifndef LIBC_SIGNAL_H
#define LIBC_SIGNAL_H

typedef void (*__sighandler_t)(int);

#define __NSIG 32

#define SIGNULL 0
#define SIGHUP 1
#define SIGINT 2
#define SIGQUIT 3
#define SIGILL 4
#define SIGTRAP 5
#define SIGABRT 6
#define SIGIOT SIGABRT
#define SIGPRIV 7
#define SIGEMT SIGPRIV
#define SIGFPE 8
#define SIGKILL 9
#define SIGBUS 10
#define SIGSEGV 11
#define SIGSYS 12
#define SIGPIPE 13
#define SIGALRM 14
#define SIGTERM 15
#define SIGURG 16
#define SIGSTOP 17
#define SIGTSTP 18
#define SIGCONT 19
#define SIGCHLD 20
#define SIGTTIN 21
#define SIGTTOU 22
#define SIGIO 23
#define SIGPOLL SIGIO
#define SIGXCPU 24
#define SIGXFSZ 25
#define SIGVTALRM 26
#define SIGPROF 27
#define SIGWINCH 28
#define SIGUSR1 29
#define SIGUSR2 30
#define SIGPWR 31

#define SIG_DFL ((__sighandler_t)0)
#define SIG_IGN ((__sighandler_t)1)
#define SIG_ERR ((__sighandler_t) - 1)

__sighandler_t signal(int sig, __sighandler_t handler);
int raise(int sig);

#endif /* LIBC_SIGNAL_H */
