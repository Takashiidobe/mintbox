long Fdelete(const char *path) {
  register long ret __asm__("d0");
  __asm__ volatile("movl %1,%%sp@-\n\t"
                   "movw %2,%%sp@-\n\t"
                   "trap #1\n\t"
                   "addql #6,%%sp"
                   : "=d"(ret)
                   : "r"(path), "i"(0x41)
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return ret;
}
