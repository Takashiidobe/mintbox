#ifndef GEMDOS_NETWORK_H
#define GEMDOS_NETWORK_H

#include "./syscall.h"
#include <stdint.h>

/* Fflush - Flush the buffer of a file. */
static inline int32_t Fflush(int16_t handle) {
  return (int32_t)trap_1_ww(0x66, handle);
}

/* Flock - Protect a portion of a file. */
static inline int32_t Flock(int16_t handle, int32_t length) {
  return (int32_t)trap_1_wwl(0x64, handle, (long)length);
}

/* Frlock - Protect a portion of a file. */
static inline int32_t Frlock(int16_t handle, int32_t start, int32_t length) {
  return (int32_t)trap_1_wwll(0x62, handle, (long)start, (long)length);
}

/* Frunlock - Unlock a portion of a file. */
static inline int32_t Frunlock(int16_t handle, int32_t start) {
  return (int32_t)trap_1_wwl(0x63, handle, (long)start);
}

/* Funlock - Unlock a portion of a file. */
static inline int32_t Funlock(int16_t handle) {
  return (int32_t)trap_1_ww(0x65, handle);
}

/* Nversion - Network identifier determine. */
static inline int32_t Nversion(void) { return (int32_t)trap_1_w(0x60); }

#endif /* GEMDOS_NETWORK_H */
