#ifndef GEMDOS_SYSTEM_H
#define GEMDOS_SYSTEM_H

#include "../include/stdint.h"
#include "./syscall.h"

// Forward declarations for structures supplied elsewhere.
typedef struct COOKIE COOKIE;
typedef struct SHARED_LIB SHARED_LIB;
typedef struct SLB_EXEC SLB_EXEC;

// Salert - Output alert or error-message.
static inline void Salert(int8_t *msg) { (void)trap_1_wl(0x13C, (long)msg); }

// Sconfig - Configuration of parts of the operating system.
static inline int32_t Sconfig(int16_t mode, int32_t flags) {
  return (int32_t)trap_1_wwl(0x33, mode, (long)flags);
}

// Scookie - Cookie jar management (disabled in FreeMiNT 1.12.4+).
static inline int32_t Scookie(int16_t action, COOKIE *cookie) {
  (void)action;
  (void)cookie;
  return -1;
}

// Shutdown - Kill all processes, sync file-systems then halt or reboot.
static inline int32_t Shutdown(int32_t mode) {
  return (int32_t)trap_1_wl(0x151, (long)mode);
}

// Slbclose - Close a shared library.
static inline int32_t Slbclose(SHARED_LIB *sl) {
  return (int32_t)trap_1_wl(0x17, (long)sl);
}

// Slbopen - Open a shared library.
static inline int32_t Slbopen(int8_t *name, int8_t *path, int32_t min_ver,
                              SHARED_LIB *sl, SLB_EXEC *fn) {
  return (int32_t)trap_1_wlllll(0x16, (long)name, (long)path, (long)min_ver,
                                (long)sl, (long)fn);
}

// Srealloc - Allocate screen memory.
static inline int32_t Srealloc(int32_t len) {
  return (int32_t)trap_1_wl(0x15, (long)len);
}

// Ssystem - Control cookie jar, memory access and various system settings.
static inline int32_t Ssystem(int16_t mode, int32_t arg1, int32_t arg2) {
  return (int32_t)trap_1_wwll(0x154, mode, (long)arg1, (long)arg2);
}

// STEFcntrl - STEmulator control functions.
static inline int32_t STEFcntrl(int16_t func, int32_t special1,
                                int32_t special2) {
  return (int32_t)trap_1_wwll(0x5DC0, func, (long)special1, (long)special2);
}

// Super - Switch supervisor-mode.
static inline int32_t Super(void *stack) {
  return (int32_t)trap_1_wl(0x20, (long)stack);
}

// Suptime - Return the current uptime and load averages.
static inline int32_t Suptime(int32_t *uptime, int32_t *loadaverage) {
  return (int32_t)trap_1_wll(0x13F, (long)uptime, (long)loadaverage);
}

// Sversion - Obtain the number of the current GEMDOS version.
static inline uint16_t Sversion(void) { return (uint16_t)trap_1_w(0x30); }

// Syield - Release CPU for other processes.
static inline void Syield(void) { (void)trap_1_w(0xFF); }

// Sync - Synchronise all mounted file-systems.
static inline void Sync(void) { (void)trap_1_w(0x150); }

// Sysconf - Obtain information about the operating system configuration.
static inline int32_t Sysconf(int16_t n) {
  return (int32_t)trap_1_ww(0x122, n);
}

#endif /* GEMDOS_SYSTEM_H */
