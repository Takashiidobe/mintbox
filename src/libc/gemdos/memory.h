#ifndef GEMDOS_MEMORY_H
#define GEMDOS_MEMORY_H

#include "./syscall.h"
#include <stdint.h>

/* Maccess - verify accessibility of a region of memory. */
static inline int32_t Maccess(void *start, int32_t size, int16_t mode) {
  return (int32_t)trap_1_wllw(0x17D, (long)start, (long)size, mode);
}

/* Maddalt - Register 'Alternative' RAM with GEMDOS. */
static inline int32_t Maddalt(void *start, int32_t size) {
  return (int32_t)trap_1_wll(0x14, (long)start, (long)size);
}

/* Malloc - Reserve a block of memory or inquire free memory. */
static inline void *Malloc(int32_t number) {
  return (void *)trap_1_wl(0x48, (long)number);
}

/* Mfree - Release a block of memory. */
static inline int32_t Mfree(void *block) {
  return (int32_t)trap_1_wl(0x49, (long)block);
}

/* Mshrink - Reduce or enlarge a memory block. */
static inline int32_t Mshrink(void *block, int32_t newsiz) {
  return (int32_t)trap_1_wwll(0x4A, (int16_t)0, (long)block, (long)newsiz);
}

/* Mvalidate - verify access to a process memory region. */
static inline int32_t Mvalidate(int16_t pid, void *start, int32_t size,
                                int32_t *flags) {
  return (int32_t)trap_1_wwlll(0x141, pid, (long)start, (long)size,
                               (long)flags);
}

/* Mxalloc - Reserve memory according to specified preferences. */
static inline void *Mxalloc(int32_t amount, int16_t mode) {
  return (void *)trap_1_wlw(0x44, (long)amount, mode);
}

#endif /* GEMDOS_MEMORY_H */
