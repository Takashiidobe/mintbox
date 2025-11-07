#include <mint/mintbind.h>
#include <limits.h>
#include <stdint.h>
#include <unistd.h>

void *sbrk(intptr_t increment) {
  if (increment <= 0 || increment > INT32_MAX) {
    return (void *)-1;
  }

  void *ptr = Malloc((int32_t)increment);
  if ((intptr_t)ptr < 0) {
    return (void *)-1;
  }

  return ptr;
}
