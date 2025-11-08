#include <mint/mintbind.h>
#include <sys/types.h>
#include <unistd.h>

pid_t getppid(void) { return (pid_t)Pgetppid(); }
