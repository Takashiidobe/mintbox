#ifndef LIBC_TERMIOS_INTERNAL_H
#define LIBC_TERMIOS_INTERNAL_H

#include <termios.h>

void __termios_shadow_apply(int fd, struct termios *tio);
void __termios_shadow_store(int fd, const struct termios *tio);

#endif /* LIBC_TERMIOS_INTERNAL_H */
