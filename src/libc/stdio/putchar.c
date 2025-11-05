#include <stdio.h>

int putchar(int c) {
  register int ret __asm__("d0") = c;

  __asm__ volatile("move.w %0, -(%%sp)\n\t"
                   "move.w #0x02, -(%%sp)\n\t"
                   "trap #1\n\t"
                   "addq.l #4, %%sp"
                   : "+d"(ret)
                   :
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");

  return ret;
}
