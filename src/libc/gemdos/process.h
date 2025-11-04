#ifndef GEMDOS_PROCESS_H
#define GEMDOS_PROCESS_H

#include "../include/stdint.h"
#include "./syscall.h"

// Forward declarations for structures supplied elsewhere.
struct sigaction;

// Pause - Suspend a process until the arrival of a signal.
static inline void Pause(void) { (void)trap_1_w(0x121); }

// Pdomain - Set or get the caller's execution domain.
static inline int16_t Pdomain(int16_t dom) {
  return (int16_t)trap_1_ww(0x119, dom);
}

// Pexec - Load and execute a program.
static inline int32_t Pexec(uint16_t mode, const int8_t *fname,
                            const void *cmdline, const void *env) {
  return (int32_t)trap_1_wwlll(0x4B, (int16_t)mode, (long)fname, (long)cmdline,
                               (long)env);
}

// Pfork - Create a copy of the current process.
static inline int16_t Pfork(void) { return (int16_t)trap_1_w(0x11B); }

// Pgetauid - Get user ID of a process at the start.
static inline int16_t Pgetauid(void) { return (int16_t)trap_1_w(0x145); }

// Pgetegid - Get effective group ID of a process.
static inline int32_t Pgetegid(void) { return (int32_t)trap_1_w(0x139); }

// Pgeteuid - Get effective user ID of a process.
static inline int32_t Pgeteuid(void) { return (int32_t)trap_1_w(0x138); }

// Pgetgid - Get group ID of a process.
static inline int16_t Pgetgid(void) { return (int16_t)trap_1_w(0x114); }

// Pgetgroups - Get supplementary group IDs for the calling process.
static inline int32_t Pgetgroups(int16_t len, int16_t *gidset) {
  return (int32_t)trap_1_wwl(0x147, len, (long)gidset);
}

// Pgetpgrp - Get current group number.
static inline int16_t Pgetpgrp(void) { return (int16_t)trap_1_w(0x10D); }

// Pgetpid - Get current process ID.
static inline int16_t Pgetpid(void) { return (int16_t)trap_1_w(0x10B); }

// Pgetppid - Get parent process ID.
static inline int16_t Pgetppid(void) { return (int16_t)trap_1_w(0x10C); }

// Pgetpriority - Get the current priority value for a process.
static inline int32_t Pgetpriority(int16_t which, int16_t who) {
  return (int32_t)trap_1_www(0x158, which, who);
}

// Pgetuid - Get user ID of a process.
static inline int16_t Pgetuid(void) { return (int16_t)trap_1_w(0x10F); }

// Pkill - Send a signal to one or more processes.
static inline int32_t Pkill(int16_t pid, int16_t sig) {
  return (int32_t)trap_1_www(0x111, pid, sig);
}

// Pmsg - Send and receive messages.
static inline int32_t Pmsg(int16_t mode, int32_t mbox, void *msg) {
  return (int32_t)trap_1_wwll(0x125, mode, (long)mbox, (long)msg);
}

// Pnice - Alter priority of the calling process.
static inline int16_t Pnice(int16_t delta) {
  return (int16_t)trap_1_ww(0x10A, delta);
}

// Prenice - Adjust priority of a specified process.
static inline int32_t Prenice(int16_t pid, int16_t delta) {
  return (int32_t)trap_1_www(0x127, pid, delta);
}

// Prusage - Obtain resource information about current process.
static inline int32_t Prusage(int32_t *r) {
  return (int32_t)trap_1_wl(0x11E, (long)r);
}

// Psemaphore - Create, use or destroy a semaphore.
static inline int32_t Psemaphore(int16_t mode, int32_t id, int32_t timeout) {
  return (int32_t)trap_1_wwll(0x134, mode, (long)id, (long)timeout);
}

// Psetauid - Set user ID of a process at the start.
static inline int16_t Psetauid(int16_t id) {
  return (int16_t)trap_1_ww(0x146, id);
}

// Psetegid - Set the effective group ID for the calling process.
static inline int32_t Psetegid(int16_t egid) {
  return (int32_t)trap_1_ww(0x144, egid);
}

// Pseteuid - Set the effective user ID for the calling process.
static inline int32_t Pseteuid(int16_t euid) {
  return (int32_t)trap_1_ww(0x143, euid);
}

// Psetgid - Alter the group ID of the calling process.
static inline int16_t Psetgid(int16_t id) {
  return (int16_t)trap_1_ww(0x115, id);
}

// Psetgroups - Set supplementary group IDs for the calling process.
static inline int32_t Psetgroups(int16_t len, const int16_t *gidset) {
  return (int32_t)trap_1_wwl(0x148, len, (long)gidset);
}

// Psetlimit - Set or obtain allocation limits of system resources.
static inline int32_t Psetlimit(int16_t lim, int32_t value) {
  return (int32_t)trap_1_wwl(0x11F, lim, (long)value);
}

// Psetpgrp - Get or set process group number of a process.
static inline int16_t Psetpgrp(int16_t pid, int16_t newgrp) {
  return (int16_t)trap_1_www(0x10E, pid, newgrp);
}

// Psetpriority - Set the current priority value for a process.
static inline int32_t Psetpriority(int16_t which, int16_t who, int16_t pri) {
  return (int32_t)trap_1_wwww(0x159, which, who, pri);
}

// Psetregid - Set the real and/or effective group ID for the calling process.
static inline int32_t Psetregid(int16_t rgid, int16_t egid) {
  return (int32_t)trap_1_www(0x14F, rgid, egid);
}

// Psetreuid - Set the real and/or effective user ID for the calling process.
static inline int32_t Psetreuid(int16_t ruid, int16_t euid) {
  return (int32_t)trap_1_www(0x14E, ruid, euid);
}

// Psetuid - Alter the user ID of a process.
static inline int16_t Psetuid(int16_t id) {
  return (int16_t)trap_1_ww(0x110, id);
}

// Psigaction - Set default action for a specified signal.
static inline int32_t Psigaction(int16_t sig, struct sigaction *act,
                                 struct sigaction *oact) {
  return (int32_t)trap_1_wwll(0x137, sig, (long)act, (long)oact);
}

// Psigblock - Alter signal mask.
static inline int32_t Psigblock(int32_t mask) {
  return (int32_t)trap_1_wl(0x116, (long)mask);
}

// Psigintr - Assign a signal to a particular exception vector.
static inline int32_t Psigintr(int16_t vec, int16_t sig) {
  return (int32_t)trap_1_www(0x13E, vec, sig);
}

// Psignal - Alter manner of signal handling.
static inline int32_t Psignal(int16_t sig, int32_t handler) {
  return (int32_t)trap_1_wwl(0x112, sig, (long)handler);
}

// Psigpause - Suspend process until the arrival of a signal.
static inline void Psigpause(int32_t mask) {
  (void)trap_1_wl(0x136, (long)mask);
}

// Psigpending - Check which signals have been sent but not processed.
static inline int32_t Psigpending(void) { return (int32_t)trap_1_w(0x123); }

// Psigreturn - Prepare exit from a signal handler.
static inline void Psigreturn(void) { (void)trap_1_w(0x11A); }

// Psigsetmask - Set or replace a signal mask.
static inline int32_t Psigsetmask(int32_t mask) {
  return (int32_t)trap_1_wl(0x117, (long)mask);
}

// Psysctl - Get or set system information.
static inline int32_t Psysctl(int32_t *name, uint32_t namelen, void *oldbuf,
                              uint32_t *oldlenp, void *newbuf,
                              uint32_t newlen) {
  return (int32_t)trap_1_wllllll(0x15E, (long)name, (long)namelen, (long)oldbuf,
                                 (long)oldlenp, (long)newbuf, (long)newlen);
}

// Pterm - Terminate a TOS program.
static inline void Pterm(uint16_t retcode) {
  (void)trap_1_ww(0x4C, (int16_t)retcode);
}

// Pterm0 - Terminate a TOS program and return 0 to caller.
static inline void Pterm0(void) { (void)trap_1_w(0x00); }

// Ptermres - Terminate a program but leave it resident.
static inline void Ptermres(int32_t keepcnt, int16_t retcode) {
  (void)trap_1_wlw(0x31, (long)keepcnt, retcode);
}

// Ptrace - Process tracing and debugging.
static inline int16_t Ptrace(int16_t request, int16_t pid, void *addr,
                             int32_t data) {
  return (int16_t)trap_1_wwwll(0x140, request, pid, (long)addr, (long)data);
}

// Pumask - Set initial creation mask for files and directories.
static inline int16_t Pumask(int16_t mode) {
  return (int16_t)trap_1_ww(0x133, mode);
}

// Pusrval - Set or query process specific information.
static inline int32_t Pusrval(int32_t val) {
  return (int32_t)trap_1_wl(0x118, (long)val);
}

// Pvfork - Create a copy of the current process.
static inline int16_t Pvfork(void) { return (int16_t)trap_1_w(0x113); }

// Pwait - Obtain the exit code of a waiting or terminated child process.
static inline int32_t Pwait(void) { return (int32_t)trap_1_w(0x109); }

// Pwait3 - Get exit code information about child processes.
static inline int32_t Pwait3(int16_t flag, int32_t *rusage) {
  return (int32_t)trap_1_wwl(0x11C, flag, (long)rusage);
}

// Pwaitpid - Get exit code information about specific child processes.
static inline int32_t Pwaitpid(int16_t pid, int16_t flag, int32_t *rusage) {
  return (int32_t)trap_1_wwwl(0x13A, pid, flag, (long)rusage);
}

#endif
/* GEMDOS_PROCESS_H  */
