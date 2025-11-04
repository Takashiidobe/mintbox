#ifndef GEMDOS_CHARACTER_H
#define GEMDOS_CHARACTER_H

#include "./syscall.h"
#include <stdint.h>

// Cauxin - Input via serial port.
static inline int32_t Cauxin(void) { return (int32_t)trap_1_w(0x03); }

// Cauxis - Check the input status of the serial port.
static inline int16_t Cauxis(void) { return (int16_t)trap_1_w(0x12); }

// Cauxos - Check the output status of the serial port.
static inline int16_t Cauxos(void) { return (int16_t)trap_1_w(0x13); }

// Cauxout - Write a character to the serial port.
static inline int32_t Cauxout(int16_t c) { return (int32_t)trap_1_ww(0x04, c); }

// Cconin - Read a character from the standard input device.
static inline int32_t Cconin(void) { return (int32_t)trap_1_w(0x01); }

// Cconis - Check whether a character is waiting in the input buffer.
static inline int32_t Cconis(void) { return (int32_t)trap_1_w(0x0B); }

// Cconos - Check status of the standard output device.
static inline int16_t Cconos(void) { return (int16_t)trap_1_w(0x10); }

// Cconout - Write a character to the standard output device.
static inline int32_t Cconout(int16_t c) { return (int32_t)trap_1_ww(0x02, c); }

// Cconrs - Read a string from the standard input.
static inline int32_t Cconrs(void *buf) {
  return (int32_t)trap_1_wl(0x0A, (long)buf);
}

// Cconws - Write a string to the standard output device.
static inline int32_t Cconws(const int8_t *buf) {
  return (int32_t)trap_1_wl(0x09, (long)buf);
}

// Cnecin - Read a character without echo.
static inline int32_t Cnecin(void) { return (int32_t)trap_1_w(0x08); }

// Cprnos - Check the status of the printer port.
static inline int16_t Cprnos(void) { return (int16_t)trap_1_w(0x11); }

// Cprnout - Write a character to the printer port.
static inline int32_t Cprnout(int16_t c) { return (int32_t)trap_1_ww(0x05, c); }

// Crawcin - Read an unbuffered character from standard input device.
static inline int32_t Crawcin(void) { return (int32_t)trap_1_w(0x07); }

// Crawio - Permit unbuffered input/output.
static inline int32_t Crawio(int16_t w) { return (int32_t)trap_1_ww(0x06, w); }

#endif /* GEMDOS_CHARACTER_H */
