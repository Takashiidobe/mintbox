#ifndef GEMDOS_XBIOS_H
#define GEMDOS_XBIOS_H

#include "./syscall.h"
#include <stdint.h>

/* Forward declaration for keyboard vector structure. */
typedef struct _KBDVECS _KBDVECS;

// Initmous - Initialise the mouse driver.
static inline void Initmous(int16_t type, void *param, void *handler) {
  (void)trap_14_wwll(0x00, type, (long)param, (long)handler);
}

// Ssbrk - Adjust supervisor memory allocation.
static inline void *Ssbrk(int16_t size) {
  return (void *)trap_14_ww(0x01, size);
}

// Physbase - Return the physical screen base address.
static inline void *Physbase(void) { return (void *)trap_14_w(0x02); }

// Logbase - Return the logical screen base address.
static inline void *Logbase(void) { return (void *)trap_14_w(0x03); }

// Getrez - Report the current video resolution.
static inline int16_t Getrez(void) { return (int16_t)trap_14_w(0x04); }

// Setscreen - Set logical and physical screen addresses and resolution.
static inline void Setscreen(void *lscrn, void *pscrn, int16_t rez) {
  (void)trap_14_wllw(0x05, (long)lscrn, (long)pscrn, rez);
}

// Setpalette - Load the colour palette.
static inline void Setpalette(const void *palptr) {
  (void)trap_14_wl(0x06, (long)palptr);
}

// Setcolor - Set a single colour register.
static inline int16_t Setcolor(int16_t colornum, int16_t mixture) {
  return (int16_t)trap_14_www(0x07, colornum, mixture);
}

// Floprd - Read sectors from a floppy disk.
static inline int16_t Floprd(void *buf, void *x, int16_t dev, int16_t sect,
                             int16_t trk, int16_t side, int16_t n) {
  return (int16_t)trap_14_wllwwwww(0x08, (long)buf, (long)x, dev, sect, trk,
                                   side, n);
}

// Flopwr - Write sectors to a floppy disk.
static inline int16_t Flopwr(const void *buf, const void *x, int16_t dev,
                             int16_t sect, int16_t trk, int16_t side,
                             int16_t n) {
  return (int16_t)trap_14_wllwwwww(0x09, (long)buf, (long)x, dev, sect, trk,
                                   side, n);
}

// Flopfmt - Format tracks on a floppy disk.
static inline int16_t Flopfmt(void *buf, void *x, int16_t dev, int16_t spt,
                              int16_t trk, int16_t sd, int16_t interleave,
                              void *m, int16_t v) {
  return (int16_t)trap_14_wllwwwwwlw(0x0A, (long)buf, (long)x, dev, spt, trk,
                                     sd, interleave, (long)m, v);
}

// Midiws - Send data to the MIDI system.
static inline void Midiws(int16_t count, const void *ptr) {
  (void)trap_14_wwl(0x0C, count, (long)ptr);
}

// Mfpint - Install an MFP interrupt handler.
static inline void Mfpint(int16_t vnum, void (*handler)(void)) {
  (void)trap_14_wwl(0x0D, vnum, (long)handler);
}

// Iorec - Return I/O record information.
static inline void *Iorec(int16_t device) {
  return (void *)trap_14_ww(0x0E, device);
}

// Rsconf - Configure the serial port hardware.
static inline int32_t Rsconf(int16_t baud, int16_t flow, int16_t uc, int16_t rs,
                             int16_t ts, int16_t sc) {
  return (int32_t)trap_14_wwwwwww(0x0F, baud, flow, uc, rs, ts, sc);
}

// Keytbl - Set or query the keyboard translation tables.
static inline void *Keytbl(void *nrml, void *shft, void *caps) {
  return (void *)trap_14_wlll(0x10, (long)nrml, (long)shft, (long)caps);
}

// Random - Return the contents of the 200Hz timer.
static inline int32_t Random(void) { return (int32_t)trap_14_w(0x11); }

// Protobt - Set disk protection info in a boot sector image.
static inline void Protobt(void *buf, int32_t serial, int16_t dsktyp,
                           int16_t exec) {
  (void)trap_14_wllww(0x12, (long)buf, serial, dsktyp, exec);
}

// Flopver - Verify sectors on a floppy disk.
static inline int16_t Flopver(void *buf, void *x, int16_t dev, int16_t sect,
                              int16_t trk, int16_t sd, int16_t n) {
  return (int16_t)trap_14_wllwwwww(0x13, (long)buf, (long)x, dev, sect, trk, sd,
                                   n);
}

// Scrdmp - Dump the screen to printer.
static inline void Scrdmp(void) { (void)trap_14_w(0x14); }

// Cursconf - Configure the mouse cursor.
static inline int16_t Cursconf(int16_t rate, int16_t attr) {
  return (int16_t)trap_14_www(0x15, rate, attr);
}

// Settime - Set the system clock from a DOS time value.
static inline void Settime(int32_t time) { (void)trap_14_wl(0x16, time); }

// Gettime - Read the system clock as a DOS time value.
static inline int32_t Gettime(void) { return (int32_t)trap_14_w(0x17); }

// Bioskeys - Update BIOS keyboard tables from IKBD state.
static inline void Bioskeys(void) { (void)trap_14_w(0x18); }

// Ikbdws - Send a command sequence to the IKBD.
static inline void Ikbdws(int16_t len_minus1, const void *ptr) {
  (void)trap_14_wwl(0x19, len_minus1, (long)ptr);
}

// Jdisint - Disable a specified interrupt vector.
static inline void Jdisint(int16_t vnum) { (void)trap_14_ww(0x1A, vnum); }

// Jenabint - Enable a specified interrupt vector.
static inline void Jenabint(int16_t vnum) { (void)trap_14_ww(0x1B, vnum); }

// Giaccess - Access the General Instrument sound chip.
static inline int16_t Giaccess(int16_t data, int16_t reg) {
  return (int16_t)trap_14_www(0x1C, data, reg);
}

// Offgibit - Clear bits in the general I/O port.
static inline void Offgibit(int16_t ormask) { (void)trap_14_ww(0x1D, ormask); }

// Ongibit - Set bits in the general I/O port.
static inline void Ongibit(int16_t andmask) { (void)trap_14_ww(0x1E, andmask); }

// Xbtimer - Configure an extended BIOS timer.
static inline void Xbtimer(int16_t timer, int16_t ctrl, int16_t data,
                           void (*handler)(void)) {
  (void)trap_14_wwwwl(0x1F, timer, ctrl, data, (long)handler);
}

// Dosound - Execute a sound command sequence.
static inline int32_t Dosound(const void *ptr) {
  return (int32_t)trap_14_wl(0x20, (long)ptr);
}

// Setprt - Configure the printer device.
static inline int16_t Setprt(int16_t config) {
  return (int16_t)trap_14_ww(0x21, config);
}

// Kbdvbase - Return the keyboard vector table base.
static inline _KBDVECS *Kbdvbase(void) { return (_KBDVECS *)trap_14_w(0x22); }

// Kbrate - Set the keyboard repeat rate.
static inline int16_t Kbrate(int16_t delay, int16_t reprate) {
  return (int16_t)trap_14_www(0x23, delay, reprate);
}

// Prtblk - Print a parameter block.
static inline void Prtblk(void *pblkptr) {
  (void)trap_14_wl(0x24, (long)pblkptr);
}

// Vsync - Wait for the vertical blank interval.
static inline void Vsync(void) { (void)trap_14_w(0x25); }

// Supexec - Execute a function in supervisor mode.
static inline int32_t Supexec(int32_t (*funcptr)(void)) {
  return (int32_t)trap_14_wl(0x26, (long)funcptr);
}

// Puntaes - Terminate the AES process.
static inline void Puntaes(void) { (void)trap_14_w(0x27); }

// Floprate - Query or set the floppy data rate.
static inline int16_t Floprate(int16_t drive, int16_t rate) {
  return (int16_t)trap_14_www(0x29, drive, rate);
}

// Blitmode - Query or set the blitter configuration.
static inline int16_t Blitmode(int16_t flag) {
  return (int16_t)trap_14_ww(0x40, flag);
}

#endif /* GEMDOS_XBIOS_H */
