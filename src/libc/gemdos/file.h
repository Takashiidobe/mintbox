#ifndef GEMDOS_FILE_H
#define GEMDOS_FILE_H

#include "./syscall.h"
#include <stdint.h>

/* Forward declarations for GEMDOS structures provided elsewhere. */
typedef struct DOSTIME DOSTIME;
typedef struct DTA DTA;
typedef struct STAT STAT;
typedef struct XATTR XATTR;
typedef struct POLLFD POLLFD;

/* Fattrib - Obtain or change file attributes. */
static inline int16_t Fattrib(const char *filename, int16_t wflag,
                              int16_t attrib) {
  return (int16_t)trap_1_wlww(0x43, (long)filename, wflag, attrib);
}

/* Fchmod - Change file access mode bits. */
static inline int32_t Fchmod(char *name, int16_t mode) {
  return (int32_t)trap_1_wlw(0x132, (long)name, mode);
}

/* Fchown - Change file ownership. */
static inline int32_t Fchown(char *name, int16_t uid, int16_t gid) {
  return (int32_t)trap_1_wlww(0x131, (long)name, uid, gid);
}

/* Fchown16 - Change file ownership with follow flag. */
static inline int32_t Fchown16(char *name, int16_t uid, int16_t gid,
                               int16_t flag) {
  return (int32_t)trap_1_wlwww(0x180, (long)name, uid, gid, flag);
}

/* Fchdir - Change the current directory using a handle. */
static inline int32_t Fchdir(int16_t handle) {
  return (int32_t)trap_1_ww(0x181, handle);
}

/* Fcntl - Control operations on file descriptors. */
static inline int32_t Fcntl(int16_t fh, int32_t arg, int16_t cmd) {
  return (int32_t)trap_1_wwlw(0x104, fh, (long)arg, cmd);
}

/* Fcreate - Create a file. */
static inline int16_t Fcreate(const char *fname, int16_t attr) {
  return (int16_t)trap_1_wlw(0x3C, (long)fname, attr);
}

/* Fdatime - Get or set the date/time stamp for a file handle. */
static inline void Fdatime(DOSTIME *timeptr, int16_t handle, int16_t wflag) {
  (void)trap_1_wlww(0x57, (long)timeptr, handle, wflag);
}

/* Fdelete - Remove a file. */
static inline int32_t Fdelete(const char *fname) {
  return (int32_t)trap_1_wl(0x41, (long)fname);
}

/* Fopen - Open a file. */
static inline int32_t Fopen(const char *fname, int16_t mode) {
  return (int32_t)trap_1_wlw(0x3D, (long)fname, mode);
}

/* Fclose - Close an open file handle. */
static inline int32_t Fclose(int16_t handle) {
  return (int32_t)trap_1_ww(0x3E, handle);
}

/* Fread - Read bytes from a file handle. */
static inline int32_t Fread(int16_t handle, int32_t count, const void *buf) {
  return (int32_t)trap_1_wwll(0x3F, handle, (long)count, (long)buf);
}

/* Fwrite - Write bytes to a file handle. */
static inline int32_t Fwrite(int16_t handle, int32_t count, const void *buf) {
  return (int32_t)trap_1_wwll(0x40, handle, (long)count, (long)buf);
}

/* Fdirfd - Obtain directory file descriptor. */
static inline int16_t Fdirfd(int32_t handle) {
  return (int16_t)trap_1_wl(0x183, (long)handle);
}

/* Fdup - Duplicate a file handle. */
static inline int16_t Fdup(int16_t handle) {
  return (int16_t)trap_1_ww(0x45, handle);
}

/* Ffchmod - Change mode of a file descriptor. */
static inline int32_t Ffchmod(int16_t fd, int16_t mode) {
  return (int32_t)trap_1_www(0x102, fd, mode);
}

/* Ffchown - Change ownership of a file descriptor. */
static inline int32_t Ffchown(int16_t fd, int16_t uid, int16_t gid) {
  return (int32_t)trap_1_wwww(0x101, fd, uid, gid);
}

/* Ffdopendir - Open a directory stream using a file descriptor. */
static inline int32_t Ffdopendir(int16_t fd) {
  return (int32_t)trap_1_ww(0x182, fd);
}

/* Fforce - Force a file handle to standard handle. */
static inline int16_t Fforce(int16_t stdh, int16_t nonstdh) {
  return (int16_t)trap_1_www(0x46, stdh, nonstdh);
}

/* Ffstat64 - Obtain 64-bit file status for a descriptor. */
static inline int32_t Ffstat64(int16_t fd, STAT *stat) {
  return (int32_t)trap_1_wwl(0x15D, fd, (long)stat);
}

/* Fgetchar - Read a character from a device or file. */
static inline int32_t Fgetchar(int16_t fh, int16_t mode) {
  return (int32_t)trap_1_www(0x107, fh, mode);
}

/* Fgetdta - Retrieve pointer to the default DTA. */
static inline DTA *Fgetdta(void) { return (DTA *)trap_1_w(0x2F); }

/* Finstat - Test input status of a handle. */
static inline int32_t Finstat(int16_t fh) {
  return (int32_t)trap_1_ww(0x105, fh);
}

/* Flink - Create a hard link. */
static inline int32_t Flink(char *oldname, int8_t *newname) {
  return (int32_t)trap_1_wll(0x12D, (long)oldname, (long)newname);
}

/* Flock - Protect a region of a file. */
static inline int32_t Flock(int16_t handle, int16_t mode, int32_t start,
                            int32_t length) {
  return (int32_t)trap_1_wwwll(0x5C, handle, mode, (long)start, (long)length);
}

/* Fmidipipe - Create a MIDI pipe. */
static inline int32_t Fmidipipe(int16_t pid, int16_t in, int16_t out) {
  return (int32_t)trap_1_wwww(0x126, pid, in, out);
}

/* Foutstat - Test output status of a handle. */
static inline int32_t Foutstat(int16_t fh) {
  return (int32_t)trap_1_ww(0x106, fh);
}

/* Fpipe - Create an unnamed pipe. */
static inline int32_t Fpipe(int16_t usrh[2]) {
  return (int32_t)trap_1_wl(0x100, (long)usrh);
}

/* Fpoll - Poll file descriptors. */
static inline int32_t Fpoll(POLLFD *fds, uint32_t nfds, uint32_t timeout) {
  return (int32_t)trap_1_wlll(0x15A, (long)fds, (long)nfds, (long)timeout);
}

/* Fputchar - Write a character to a device or file. */
static inline int32_t Fputchar(int16_t fh, int32_t ch, int16_t mode) {
  return (int32_t)trap_1_wwlw(0x108, fh, (long)ch, mode);
}

/* Freadlink - Read a symbolic link. */
static inline int32_t Freadlink(int16_t bufsiz, char *buf, int8_t *name) {
  return (int32_t)trap_1_wwll(0x12F, bufsiz, (long)buf, (long)name);
}

/* Frename - Rename a file. */
static inline int32_t Frename(const char *oldname, const char *newname) {
  return (int32_t)trap_1_wwll(0x56, 0, (long)oldname, (long)newname);
}

/* Fseek - Seek within a file. */
static inline int32_t Fseek(int32_t offset, int16_t handle, int16_t seekmode) {
  return (int32_t)trap_1_wlww(0x42, (long)offset, handle, seekmode);
}

/* Fseek64 - Seek within a file using 64-bit offsets. */
static inline int32_t Fseek64(int32_t hioffset, uint32_t lowoffset,
                              int16_t handle, int16_t seekmode,
                              int64_t *newpos) {
  return (int32_t)trap_1_wllwwl(0x14C, (long)hioffset, (long)lowoffset, handle,
                                seekmode, (long)newpos);
}

/* Fselect - Select on file descriptors. */
static inline int32_t Fselect(uint16_t timeout, int32_t *rfds, int32_t *wfds,
                              int32_t *xfds) {
  return (int32_t)trap_1_wwlll(0x11D, timeout, (long)rfds, (long)wfds,
                               (long)xfds);
}

/* Fsetdta - Set the default DTA pointer. */
static inline void Fsetdta(DTA *buf) { (void)trap_1_wl(0x1A, (long)buf); }

/* Fsfirst - Initiate a file search. */
static inline int32_t Fsfirst(const char *filename, int16_t attr) {
  return (int32_t)trap_1_wlw(0x4E, (long)filename, attr);
}

/* Fsnext - Continue a file search. */
static inline int16_t Fsnext(void) { return (int16_t)trap_1_w(0x4F); }

/* Fsymlink - Create a symbolic link. */
static inline int32_t Fsymlink(char *oldname, char *newname) {
  return (int32_t)trap_1_wll(0x12E, (long)oldname, (long)newname);
}

/* Fstat64 - Obtain 64-bit file status information. */
static inline int32_t Fstat64(int16_t flag, char *name, STAT *stat) {
  return (int32_t)trap_1_wwll(0x14B, flag, (long)name, (long)stat);
}

/* Fsync - Synchronize a file's in-core state with storage. */
static inline int16_t Fsync(int16_t handle) {
  return (int16_t)trap_1_ww(0x103, handle);
}

/* Fxattr - Get or set extended file attributes. */
static inline int32_t Fxattr(int16_t flag, char *name, XATTR *xattr) {
  return (int32_t)trap_1_wwll(0x12C, flag, (long)name, (long)xattr);
}

#endif /* GEMDOS_FILE_H */
