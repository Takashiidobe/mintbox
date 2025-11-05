#include "./internal.h"
#include <string.h>

#define TERMIOS_SHADOW_SLOTS 8

struct termios_shadow_entry {
  int fd;
  unsigned char in_use;
  unsigned char vmin;
  unsigned char vtime;
};

static struct termios_shadow_entry shadow_table[TERMIOS_SHADOW_SLOTS];

static struct termios_shadow_entry *shadow_find(int fd) {
  if (fd < 0)
    return NULL;
  for (int i = 0; i < TERMIOS_SHADOW_SLOTS; ++i) {
    if (shadow_table[i].in_use && shadow_table[i].fd == fd)
      return &shadow_table[i];
  }
  return NULL;
}

static struct termios_shadow_entry *shadow_ensure(int fd) {
  struct termios_shadow_entry *entry = shadow_find(fd);
  if (entry)
    return entry;
  for (int i = 0; i < TERMIOS_SHADOW_SLOTS; ++i) {
    if (!shadow_table[i].in_use) {
      shadow_table[i].in_use = 1;
      shadow_table[i].fd = fd;
      shadow_table[i].vmin = 1;
      shadow_table[i].vtime = 0;
      return &shadow_table[i];
    }
  }
  return NULL;
}

void __termios_shadow_apply(int fd, struct termios *tio) {
  if (!tio)
    return;
  struct termios_shadow_entry *entry = shadow_find(fd);
  if (entry) {
    tio->c_cc[VMIN] = entry->vmin;
    tio->c_cc[VTIME] = entry->vtime;
  } else {
    if (tio->c_cc[VMIN] == 0)
      tio->c_cc[VMIN] = 1;
    /* leave VTIME as reported */
  }
}

void __termios_shadow_store(int fd, const struct termios *tio) {
  if (!tio)
    return;
  struct termios_shadow_entry *entry = shadow_ensure(fd);
  if (!entry)
    return;
  entry->vmin = tio->c_cc[VMIN];
  entry->vtime = tio->c_cc[VTIME];
}
