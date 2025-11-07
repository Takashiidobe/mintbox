#include <stddef.h>
#include <sys/uptime.h>

#include <mint/mintbind.h>

int suptime(int32_t *uptime, int32_t loadaverage[3]) {
  if (uptime == NULL) {
    return -1;
  }

  return (int)Suptime(uptime, loadaverage);
}
