#include <stdlib.h>
#include <sys/time.h>

#include "./gemdos/time.h"

int gettimeofday(struct timeval *tv, struct timezone *tz) {
  if (tv == NULL) {
    return -1;
  }

  return (int)Tgettimeofday(tv, tz);
}
