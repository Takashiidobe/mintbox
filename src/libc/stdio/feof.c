#include "./internal.h"
#include <stdio.h>

int feof(FILE *stream) {
  if (!stream)
    return 1;
  return (stream->state & FILE_STATE_EOF) != 0;
}
