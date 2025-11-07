#include "stdlib.h"

int raise(int sig) { return kill(getpid(), sig); }
