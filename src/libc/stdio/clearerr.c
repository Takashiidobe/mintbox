#include "./internal.h"
#include <stdio.h>

void clearerr(FILE *stream) {
  if (!stream)
    return;
  __stdio_clear_state(stream, FILE_STATE_EOF | FILE_STATE_ERR);
}
