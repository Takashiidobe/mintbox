#include "./internal.h"
#include <mint/mintbind.h>
#include <stdio.h>

int fcloseall(void) {
  int status = 0;
  FILE *pool = __stdio_file_pool();
  int pool_size = __stdio_file_pool_size();

  for (int i = 0; i < pool_size; ++i) {
    FILE *file = &pool[i];
    if (!(file->flags & FILE_FLAG_INUSE))
      continue;
    if (file->flags & FILE_FLAG_STATIC)
      continue;

    if (file->handle >= 0) {
      long ret = Fclose((short)file->handle);
      if (ret < 0)
        status = EOF;
    }

    __stdio_release_file(file);
  }

  return status;
}
