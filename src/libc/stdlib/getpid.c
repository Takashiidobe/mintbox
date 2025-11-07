#include "../gemdos/process.h"
#include <bits/types.h>

__pid_t getpid(void) { return Pgetpid(); }
