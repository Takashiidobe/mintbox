#ifndef GEMDOS_FILE_H
#define GEMDOS_FILE_H
#include "./syscall.h"

#define Fopen(fn, mode)                                                        \
  (long)trap_1_wlw((short)(0x3D), (long)(fn), (short)(mode))
#define Fclose(handle) (long)trap_1_ww((short)(0x3E), (short)(handle))
#define Fread(handle, cnt, buf)                                                \
  (long)trap_1_wwll((short)(0x3F), (short)(handle), (long)(cnt), (long)(buf))
#define Fwrite(handle, cnt, buf)                                               \
  (long)trap_1_wwll((short)(0x40), (short)(handle), (long)(cnt), (long)(buf))
#endif
