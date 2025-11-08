#include <mint/mintbind.h>
#include <sys/types.h>
#include <unistd.h>

uid_t getuid(void) { return (uid_t)Pgetuid(); }
