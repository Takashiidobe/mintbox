#include <stdio.h>
#include <unistd.h>

void rewind(FILE *stream) {
  if (!stream)
    return;
  fseek(stream, 0, SEEK_SET);
  clearerr(stream);
}
