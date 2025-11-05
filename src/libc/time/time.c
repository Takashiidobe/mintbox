#include <sys/time.h>
#include <time.h>

time_t time(time_t *tloc) {
  struct timeval tv;
  if (gettimeofday(&tv, NULL) < 0) {
    return (time_t)-1;
  }

  if (tloc) {
    *tloc = (time_t)tv.tv_sec;
  }

  return (time_t)tv.tv_sec;
}
