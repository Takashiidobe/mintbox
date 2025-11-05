# Mintbox

Minimalistic CLI utilities for Atari Mint.

## Credits

The libc implementation has code from
[Mintlib](https://github.com/freemint/mintlib/) as well as
[Libcmini](https://github.com/freemint/libcmini). Most of the syscall
code implementation comes from libcmini.

The documentation for
[Freemint](https://freemint.github.io/tos.hyp/en/index.html) has also
been invaluable in implementing libc, by explaining what most of the
syscalls do, their error messages, and constants used by functions like
ioctl.
