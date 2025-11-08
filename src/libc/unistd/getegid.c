#include <mint/mintbind.h>
#include <sys/types.h>
#include <unistd.h>

gid_t getegid(void) { return (gid_t)Pgetegid(); }
