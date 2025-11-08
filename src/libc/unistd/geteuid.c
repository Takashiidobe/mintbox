#include <mint/mintbind.h>
#include <sys/types.h>
#include <unistd.h>

uid_t geteuid(void) { return (uid_t)Pgeteuid(); }
