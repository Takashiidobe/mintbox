#include <mint/mintbind.h>
#include <sys/types.h>
#include <unistd.h>

gid_t getgid(void) { return (gid_t)Pgetgid(); }
