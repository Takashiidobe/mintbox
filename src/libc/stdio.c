#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_FLAG_INUSE 0x01
#define FILE_FLAG_STATIC 0x02

struct __file {
  int handle;
  unsigned char flags;
};

static struct __file __stdin_file = {0, FILE_FLAG_INUSE | FILE_FLAG_STATIC};
static struct __file __stdout_file = {1, FILE_FLAG_INUSE | FILE_FLAG_STATIC};
static struct __file __stderr_file = {2, FILE_FLAG_INUSE | FILE_FLAG_STATIC};

FILE *stdin = &__stdin_file;
FILE *stdout = &__stdout_file;
FILE *stderr = &__stderr_file;

#define FILE_POOL_SIZE 8
static struct __file __file_pool[FILE_POOL_SIZE];

static FILE *alloc_file(void) {
  for (int i = 0; i < FILE_POOL_SIZE; ++i) {
    if (!(__file_pool[i].flags & FILE_FLAG_INUSE)) {
      __file_pool[i].flags = FILE_FLAG_INUSE;
      __file_pool[i].handle = -1;
      return &__file_pool[i];
    }
  }
  return NULL;
}

static void release_file(FILE *file) {
  if (!file)
    return;
  file->flags = 0;
  file->handle = -1;
}

static long gemdos_fopen(const char *path, short mode) {
  register long ret __asm__("d0");
  short mode_copy = mode;
  __asm__ volatile("movw %3,%%sp@-\n\t"
                   "movl %2,%%sp@-\n\t"
                   "movw %1,%%sp@-\n\t"
                   "trap #1\n\t"
                   "addql #8,%%sp"
                   : "=d"(ret)
                   : "r"(path), "m"(mode_copy), "i"(0x3D)
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return ret;
}

static long gemdos_fclose(short handle) {
  register long ret __asm__("d0");
  short handle_copy = handle;
  __asm__ volatile("movw %2,%%sp@-\n\t"
                   "movw %1,%%sp@-\n\t"
                   "trap #1\n\t"
                   "addql #4,%%sp"
                   : "=d"(ret)
                   : "m"(handle_copy), "i"(0x3E)
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return ret;
}

static long gemdos_fread(short handle, long count, void *buffer) {
  register long ret __asm__("d0");
  short handle_copy = handle;
  long count_copy = count;
  void *buffer_copy = buffer;
  __asm__ volatile("movl %4,%%sp@-\n\t"
                   "movl %3,%%sp@-\n\t"
                   "movw %2,%%sp@-\n\t"
                   "movw %1,%%sp@-\n\t"
                   "trap #1\n\t"
                   "lea %%sp@(12),%%sp"
                   : "=d"(ret)
                   : "m"(handle_copy), "r"(count_copy), "r"(buffer_copy),
                     "i"(0x3F)
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return ret;
}

static long gemdos_fwrite(short handle, long count, const void *buffer) {
  register long ret __asm__("d0");
  short handle_copy = handle;
  long count_copy = count;
  const void *buffer_copy = buffer;
  __asm__ volatile("movl %3,%%sp@-\n\t"
                   "movl %2,%%sp@-\n\t"
                   "movw %1,%%sp@-\n\t"
                   "movw %4,%%sp@-\n\t"
                   "trap #1\n\t"
                   "lea 12(%%sp),%%sp"
                   : "=d"(ret)
                   : "m"(handle_copy), "r"(count_copy), "r"(buffer_copy),
                     "i"(0x40)
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return ret;
}

static size_t console_write(const unsigned char *data, size_t length) {
  size_t written = 0;
  while (written < length) {
    unsigned char ch = data[written];
    if (ch == '\n') {
      putchar('\r');
    }
    putchar(ch);
    ++written;
  }
  return written;
}

FILE *fopen(const char *path, const char *mode) {
  if (!path || !mode)
    return NULL;

  short access = 0;
  if (mode[0] == 'r') {
    access = 0; /* read-only */
  } else {
    return NULL;
  }

  long handle = gemdos_fopen(path, access);
  if (handle < 0)
    return NULL;

  FILE *file = alloc_file();
  if (!file) {
    gemdos_fclose((short)handle);
    return NULL;
  }

  file->handle = (int)handle;
  return file;
}

int fclose(FILE *stream) {
  if (!stream)
    return EOF;

  if (stream->flags & FILE_FLAG_STATIC)
    return 0;

  long ret = gemdos_fclose((short)stream->handle);
  release_file(stream);
  return ret < 0 ? EOF : 0;
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  if (!stream || !ptr || size == 0 || nmemb == 0)
    return 0;

  long total = (long)(size * nmemb);
  long ret = gemdos_fread((short)stream->handle, total, ptr);
  if (ret <= 0)
    return 0;

  return (size_t)(ret / (long)size);
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
  if (!stream || !ptr || size == 0 || nmemb == 0)
    return 0;

  size_t total_bytes = size * nmemb;

  if ((stream->flags & FILE_FLAG_STATIC) &&
      (stream->handle == 1 || stream->handle == 2)) {
    size_t written = console_write((const unsigned char *)ptr, total_bytes);
    return written / size;
  }

  long ret = gemdos_fwrite((short)stream->handle, (long)total_bytes, ptr);
  if (ret <= 0)
    return 0;

  return (size_t)(ret / (long)size);
}

int fprintf(FILE *stream, const char *format, ...) {
  if (!stream || !format)
    return EOF;

  size_t len = strlen(format);
  size_t written = fwrite(format, 1, len, stream);
  return written == len ? (int)written : EOF;
}

int fputs(const char *s, FILE *stream) {
  if (!s || !stream)
    return EOF;

  size_t len = strlen(s);
  size_t written = fwrite(s, 1, len, stream);
  return written == len ? 0 : EOF;
}
