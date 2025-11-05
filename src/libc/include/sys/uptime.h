#ifndef LIBC_SYS_UPTIME_H
#define LIBC_SYS_UPTIME_H

#include <stdint.h>

int suptime(int32_t *uptime, int32_t loadaverage[3]);

#endif /* LIBC_SYS_UPTIME_H */
