#include <mint/mintbind.h>
#include <stdint.h>
#include <stdlib.h>

__attribute__((__noreturn__)) void exit(int status) {
  Pterm((uint16_t)status);
  __builtin_unreachable();
}
