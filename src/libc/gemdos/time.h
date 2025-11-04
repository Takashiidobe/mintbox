#ifndef GEMDOS_TIME_H
#define GEMDOS_TIME_H

#include "../include/stdint.h"
#include "./syscall.h"

/* Forward declarations for structures supplied elsewhere. */
typedef struct timeval timeval;
typedef struct timezone timezone;

// Tadjtime - correct the time to synchronize the system clock.
static inline int32_t Tadjtime(const timeval *delta, timeval *olddelta) {
  return (int32_t)trap_1_wll(0x157, (long)delta, (long)olddelta);
}

// Talarm - Reads/sets a process alarm for the current process.
static inline int32_t Talarm(int32_t time) {
  return (int32_t)trap_1_wl(0x120, (long)time);
}

// Tgetdate - Obtain date.
static inline uint16_t Tgetdate(void) { return (uint16_t)trap_1_w(0x2A); }

// Tgettime - Obtain the time.
static inline uint32_t Tgettime(void) { return (uint32_t)trap_1_w(0x2C); }

// Tgettimeofday - Interrogate the state of the internal, high resolution system
// clock.
static inline int32_t Tgettimeofday(timeval *tv, timezone *tzp) {
  return (int32_t)trap_1_wll(0x155, (long)tv, (long)tzp);
}

// Tmalarm - Interrogates the state of the internal, high resolution
// system clock.
static inline int32_t Tmalarm(int32_t time) {
  return (int32_t)trap_1_wl(0x13D, (long)time);
}

// Tsetdate - Set the date.
static inline int16_t Tsetdate(uint16_t date) {
  return (int16_t)trap_1_ww(0x2B, (short)date);
}

// Tsetitimer - Control a periodic timer.
static inline int32_t Tsetitimer(int16_t which, int32_t *interval,
                                 int32_t *value, int32_t *ointerval,
                                 int32_t *ovalue) {
  return (int32_t)trap_1_wwllll(0x149, which, (long)interval, (long)value,
                                (long)ointerval, (long)ovalue);
}

// Tsettime - Set the time.
static inline int16_t Tsettime(uint16_t time) {
  return (int16_t)trap_1_ww(0x2D, (short)time);
}

// Tsettimeofday - Sets the state of the internal, high resolution system clock.
static inline int32_t Tsettimeofday(timeval *tv, timezone *tzp) {
  return (int32_t)trap_1_wll(0x156, (long)tv, (long)tzp);
}

#endif /* GEMDOS_TIME_H */
