#ifndef GEMDOS_BIOS_H
#define GEMDOS_BIOS_H

#include "./syscall.h"
#include <stdint.h>

// Getmpb - Obtain the memory parameter block information.
static inline void Getmpb(void *ptr) { (void)trap_13_wl(0x00, (long)ptr); }

// Bconstat - Test if a character is waiting on the console device.
static inline int16_t Bconstat(int16_t dev) {
  return (int16_t)trap_13_ww(0x01, dev);
}

// Bconin - Read a character from the console device.
static inline int32_t Bconin(int16_t dev) {
  return (int32_t)trap_13_ww(0x02, dev);
}

// Bconout - Write a character to the console device.
static inline int32_t Bconout(int16_t dev, int16_t c) {
  return (int32_t)trap_13_www(0x03, dev, (int16_t)(c & 0xFF));
}

// Rwabs - Raw sector I/O on a block device.
static inline int32_t Rwabs(int16_t rwflag, void *buf, int16_t n,
                            int16_t sector, int16_t dev) {
  return (int32_t)trap_13_wwlwww(0x04, rwflag, (long)buf, n, sector, dev);
}

// Lrwabs - Raw sector I/O with logical sector addressing.
static inline int32_t Lrwabs(int16_t rwflag, void *buf, int16_t n,
                             int32_t sector, int16_t dev) {
  return (int32_t)trap_13_wwlwwwl(0x04, rwflag, (long)buf, n, -1, dev,
                                  (long)sector);
}

// Setexc - Install an exception vector handler.
static inline void (*Setexc(int16_t vnum, void (*vptr)(void)))(void) {
  return (void (*)(void))trap_13_wwl(0x05, vnum, (long)vptr);
}

// Tickcal - Return the configured tick calibration value.
static inline int32_t Tickcal(void) { return (int32_t)trap_13_w(0x06); }

// Getbpb - Fetch the BIOS parameter block for a drive.
static inline void *Getbpb(int16_t dev) {
  return (void *)trap_13_ww(0x07, dev);
}

// Bcostat - Test if a character is waiting on the auxiliary console.
static inline int16_t Bcostat(int16_t dev) {
  return (int16_t)trap_13_ww(0x08, dev);
}

// Mediach - Report media change status for a drive.
static inline int16_t Mediach(int16_t dev) {
  return (int16_t)trap_13_ww(0x09, dev);
}

// Drvmap - Return a bitmap of currently mounted drives.
static inline int32_t Drvmap(void) { return (int32_t)trap_13_w(0x0A); }

// Kbshift - Read or set the keyboard shift state.
static inline int32_t Kbshift(int16_t data) {
  return (int32_t)trap_13_ww(0x0B, data);
}

// Getshift - Read the current keyboard shift state.
static inline int32_t Getshift(void) { return Kbshift(-1); }

#endif /* GEMDOS_BIOS_H */
