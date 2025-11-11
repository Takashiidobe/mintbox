#ifndef LIBC_SIGNAL_H
#define LIBC_SIGNAL_H

typedef void (*__sighandler_t)(int);
typedef unsigned long sigset_t;
typedef int sig_atomic_t;

#define __NSIG 32
#define NSIG __NSIG

#define __sigmask(sig) (((sigset_t)1U) << (sig))
#define sigmask(sig) __sigmask(sig)

#define __sigemptyset(set) ((*(set) = (sigset_t)0), 0)
#define __sigfillset(set) ((*(set) = ~(sigset_t)0), 0)
#define __sigaddset(set, sig) ((*set |= __sigmask(sig)), 0)
#define __sigdelset(set, sig) ((*set &= ~__sigmask(sig)), 0)
#define __sigismember(set, sig) (((*(set)) & __sigmask(sig)) ? 1 : 0)

#define SIG_SETMASK 0
#define SIG_BLOCK 1
#define SIG_UNBLOCK 2

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
#ifndef SIG_HOLD
#define SIG_HOLD ((__sighandler_t)2)
#endif
#ifndef BADSIG
#define BADSIG SIG_ERR
#endif

#define SIG_ERR ((__sighandler_t) - 1)

struct sigaction {
  __sighandler_t sa_handler;
  sigset_t sa_mask;
  int sa_flags;
};

__sighandler_t signal(int sig, __sighandler_t handler);
int raise(int sig);
int sigaction(int sig, const struct sigaction *act, struct sigaction *oldact);
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int sig);
int sigdelset(sigset_t *set, int sig);
int sigismember(const sigset_t *set, int sig);
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
int sigpending(sigset_t *set);
int sigsuspend(const sigset_t *mask);

#endif /* LIBC_SIGNAL_H */
