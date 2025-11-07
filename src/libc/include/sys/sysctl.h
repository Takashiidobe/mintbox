#ifndef LIBC_SYSCTL_H
#define LIBC_SYSCTL_H

int sysctl(int *name, unsigned long name_len, void *old,
           unsigned long *old_len_ptr, const void *n, unsigned long new_len);

#endif
