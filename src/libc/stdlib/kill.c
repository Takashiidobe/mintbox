#include "sys/types.h"
#include <mint/mintbind.h>

int kill(pid_t pid, int sig) { return Pkill(pid, sig); }
