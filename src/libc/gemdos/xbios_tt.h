#ifndef GEMDOS_XBIOS_TT_H
#define GEMDOS_XBIOS_TT_H

#include "./syscall.h"
#include <stdint.h>

// EsetShift - Set extended video shifter mode.
static inline void EsetShift(int16_t mode) { (void)trap_14_ww(80, mode); }

// EgetShift - Get current extended video shifter mode.
static inline int16_t EgetShift(void) { return (int16_t)trap_14_w(81); }

// EsetBank - Select the active video memory bank.
static inline int16_t EsetBank(int16_t bank) {
  return (int16_t)trap_14_ww(82, bank);
}

// EsetColor - Set extended colour register value.
static inline int16_t EsetColor(int16_t num, int16_t val) {
  return (int16_t)trap_14_www(83, num, val);
}

// EsetPalette - Load extended palette entries.
static inline void EsetPalette(int16_t start, int16_t count, const void *ptr) {
  (void)trap_14_wwwl(84, start, count, (long)ptr);
}

// EgetPalette - Read extended palette entries.
static inline void EgetPalette(int16_t start, int16_t count, void *ptr) {
  (void)trap_14_wwwl(85, start, count, (long)ptr);
}

// EsetGray - Enable or disable grayscale mode.
static inline int16_t EsetGray(int16_t mode) {
  return (int16_t)trap_14_ww(86, mode);
}

// EsetSmear - Configure smear reduction mode.
static inline int16_t EsetSmear(int16_t mode) {
  return (int16_t)trap_14_ww(87, mode);
}

// DMAread - Read sectors using the DMA controller.
static inline int32_t DMAread(int32_t sector, int16_t count, void *buffer,
                              int16_t devno) {
  return (int32_t)trap_14_wlwlw(0x2A, sector, count, (long)buffer, devno);
}

// DMAwrite - Write sectors using the DMA controller.
static inline int32_t DMAwrite(int32_t sector, int16_t count,
                               const void *buffer, int16_t devno) {
  return (int32_t)trap_14_wlwlw(0x2B, sector, count, (long)buffer, devno);
}

// Bconmap - Remap console device handles.
static inline int32_t Bconmap(int16_t dev) {
  return (int32_t)trap_14_ww(0x2C, dev);
}

// NVMaccess - Access non-volatile memory storage.
static inline int16_t NVMaccess(int16_t op, int16_t start, int16_t count,
                                void *buf) {
  return (int16_t)trap_14_wwwwl(0x2E, op, start, count, (long)buf);
}

// Waketime - Schedule a wake-up with DOS date/time values.
static inline void Waketime(uint16_t w_date, uint16_t w_time) {
  (void)trap_14_www(0x2F, (short)w_date, (short)w_time);
}

#endif /* GEMDOS_XBIOS_TT_H */
