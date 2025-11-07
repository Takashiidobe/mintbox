#include <stdlib.h>

int atexit(void (*fn)(void)) { return 0; }
int _atexit(void (*fn)(void)) { return atexit(fn); }
