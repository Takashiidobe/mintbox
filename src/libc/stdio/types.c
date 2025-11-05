#include "./internal.h"

static struct __file __stdin_file = {0, FILE_FLAG_INUSE | FILE_FLAG_STATIC};
static struct __file __stdout_file = {1, FILE_FLAG_INUSE | FILE_FLAG_STATIC};
static struct __file __stderr_file = {2, FILE_FLAG_INUSE | FILE_FLAG_STATIC};

FILE *stdin = &__stdin_file;
FILE *stdout = &__stdout_file;
FILE *stderr = &__stderr_file;

#define FILE_POOL_SIZE 8
static struct __file __file_pool[FILE_POOL_SIZE];

FILE *__stdio_alloc_file(void) {
  for (int i = 0; i < FILE_POOL_SIZE; ++i) {
    if (!(__file_pool[i].flags & FILE_FLAG_INUSE)) {
      __file_pool[i].flags = FILE_FLAG_INUSE;
      __file_pool[i].handle = -1;
      return &__file_pool[i];
    }
  }
  return NULL;
}

void __stdio_release_file(FILE *file) {
  if (!file)
    return;
  file->flags = 0;
  file->handle = -1;
}

FILE *__stdio_file_pool(void) {
  return __file_pool;
}

int __stdio_file_pool_size(void) {
  return FILE_POOL_SIZE;
}
