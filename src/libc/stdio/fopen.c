#include "./internal.h"
#include <mint/mintbind.h>

FILE *fopen(const char *path, const char *mode) {
  if (!path || !mode)
    return NULL;

  short access = 0;
  if (mode[0] == 'r') {
    access = 0; /* read-only */
  } else {
    return NULL;
  }

  long handle = Fopen(path, access);
  if (handle < 0)
    return NULL;

  FILE *file = __stdio_alloc_file();
  if (!file) {
    Fclose((short)handle);
    return NULL;
  }

  file->handle = (int)handle;
  return file;
}
