#include <mint/mintbind.h>

int sysctl(int *name, unsigned long name_len, void *old,
           unsigned long *old_len_ptr, const void *n, unsigned long new_len) {

  return Psysctl(name, name_len, old, (void *)old_len_ptr, (void *)n, new_len);
}
