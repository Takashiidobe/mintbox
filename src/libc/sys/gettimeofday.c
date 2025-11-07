#include <stdlib.h>
#include <sys/time.h>

#include <mint/mintbind.h>

int gettimeofday(struct timeval *tv, struct timezone *tz) {
  if (tv == NULL) {
    return -1;
  }

  return (int)Tgettimeofday(tv, tz);
}
