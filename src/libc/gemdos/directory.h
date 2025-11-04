#ifndef GEMDOS_DIRECTORY_H
#define GEMDOS_DIRECTORY_H

#include "../include/stdint.h"
#include "./syscall.h"

/* Forward declarations for GEMDOS structures provided elsewhere. */
typedef struct DISKINFO DISKINFO;
typedef struct XATTR XATTR;

// Dchroot - Change the root directory for the calling process.
static inline int32_t Dchroot(const int8_t *path) {
  return (int32_t)trap_1_wl(0x14A, (long)path);
}

// Dclosedir - Close a specified directory.
static inline int32_t Dclosedir(int32_t dirhandle) {
  return (int32_t)trap_1_wl(0x12B, (long)dirhandle);
}

// Dcntl - Execute a file-system-specific operation on a file or directory.
static inline int32_t Dcntl(int16_t cmd, int8_t *name, int32_t arg) {
  return (int32_t)trap_1_wwll(0x130, cmd, (long)name, (long)arg);
}

// Dcreate - Create a directory.
static inline int32_t Dcreate(const int8_t *path) {
  return (int32_t)trap_1_wl(0x39, (long)path);
}

// Ddelete - Delete a directory.
static inline int32_t Ddelete(const int8_t *path) {
  return (int32_t)trap_1_wl(0x3A, (long)path);
}

// Dfree - Obtain free and total capacity of a drive.
static inline int16_t Dfree(DISKINFO *buf, int16_t driveno) {
  return (int16_t)trap_1_wlw(0x36, (long)buf, driveno);
}

// Dgetcwd - Obtain the current directory of a process.
static inline int32_t Dgetcwd(int8_t *path, int16_t drv, int16_t size) {
  return (int32_t)trap_1_wlww(0x13B, (long)path, drv, size);
}

// Dgetdrv - Obtain the current drive.
static inline int16_t Dgetdrv(void) { return (int16_t)trap_1_w(0x19); }

// Dgetpath - Obtain current path specification.
static inline int16_t Dgetpath(int8_t *path, int16_t driveno) {
  return (int16_t)trap_1_wlw(0x47, (long)path, driveno);
}

// Dlock - Lock a BIOS device or release it again.
static inline int32_t Dlock(int16_t mode, int16_t drv) {
  return (int32_t)trap_1_www(0x135, mode, drv);
}

// Dopendir - Open a specified directory for reading.
static inline int32_t Dopendir(int8_t *name, int16_t flag) {
  return (int32_t)trap_1_wlw(0x128, (long)name, flag);
}

// Dpathconf - Obtain information about a file-system.
static inline int32_t Dpathconf(int8_t *name, int16_t mode) {
  return (int32_t)trap_1_wlw(0x124, (long)name, mode);
}

// Dreaddir - Read directory information.
static inline int32_t Dreaddir(int16_t len, int32_t dirhandle, int8_t *buf) {
  return (int32_t)trap_1_wwll(0x129, len, (long)dirhandle, (long)buf);
}

// Dreadlabel - Read file-system label.
static inline int32_t Dreadlabel(const int8_t *path, int8_t *label,
                                 int16_t length) {
  return (int32_t)trap_1_wllw(0x152, (long)path, (long)label, length);
}

// Drewinddir - Rewind the specified directory to the first entry.
static inline int32_t Drewinddir(int32_t handle) {
  return (int32_t)trap_1_wl(0x12A, (long)handle);
}

// Dsetdrv - Set the current drive and return a bitmap of mounted drives.
static inline int32_t Dsetdrv(int16_t drv) {
  return (int32_t)trap_1_ww(0x0E, drv);
}

// Dsetkey - Set the key/passphrase for a drive.
static inline int32_t Dsetkey(int32_t hidev, int32_t lowdev, int8_t *key,
                              int16_t cipher) {
  return (int32_t)trap_1_wlllw(0x14D, (long)hidev, (long)lowdev, (long)key,
                               cipher);
}

// Dsetpath - Set the current directory.
static inline int16_t Dsetpath(const int8_t *path) {
  return (int16_t)trap_1_wl(0x3B, (long)path);
}

// Dwritelabel - Set file-system label.
static inline int32_t Dwritelabel(const int8_t *path, const int8_t *label) {
  return (int32_t)trap_1_wll(0x153, (long)path, (long)label);
}

// Dxopendir - Open directory for reading.
static inline int32_t Dxopendir(int8_t *name, int16_t flag) {
  return (int32_t)trap_1_wlw(0x510, (long)name, flag);
}

// Dxreaddir - Read directory information and obtain attributes.
static inline int32_t Dxreaddir(int16_t ln, int32_t dirh, int8_t *buf,
                                XATTR *xattr, int32_t *xr) {
  return (int32_t)trap_1_wwllll(0x142, ln, (long)dirh, (long)buf, (long)xattr,
                                (long)xr);
}

#endif /* GEMDOS_DIRECTORY_H */
