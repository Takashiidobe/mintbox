#include "./internal.h"

int fileno(FILE *stream) { return stream->handle; }
