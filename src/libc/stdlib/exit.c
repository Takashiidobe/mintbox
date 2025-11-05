#include "../gemdos/process.h"
#include <stdint.h>
#include <stdlib.h>

__attribute__((__noreturn__)) void exit(int status) {
  Pterm((uint16_t)status);

  // If the OS call unexpectedly returns, spin to avoid falling through.
  for (;;) {
  }
}
