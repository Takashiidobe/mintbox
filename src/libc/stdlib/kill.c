#include "../gemdos/process.h"
#include "sys/types.h"

int kill(pid_t pid, int sig) { return Pkill(pid, sig); }
