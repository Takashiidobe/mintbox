#define trap_1_ww(n, a)                                                        \
  __extension__({                                                              \
    register long ret __asm__("d0");                                           \
    short _a = (short)(a);                                                     \
                                                                               \
    __asm__ volatile("movw	%2,%%sp@-\n\t"                                      \
                     "movw	%1,%%sp@-\n\t"                                      \
                     "trap	#1\n\t"                                             \
                     "addql	#4,%%sp"                                           \
                     : "=r"(ret)       /* outputs */                           \
                     : "g"(n), "r"(_a) /* inputs  */                           \
                     : "d1", "d2", "a0", "a1", "a2",                           \
                       "cc", /* clobbered regs */                              \
                       "memory");                                              \
    ret;                                                                       \
  })

#define trap_1_wlw(n, a, b)                                                    \
  __extension__({                                                              \
    register long ret __asm__("d0");                                           \
    long _a = (long)(a);                                                       \
    short _b = (short)(b);                                                     \
                                                                               \
    __asm__ volatile("movw	%3,%%sp@-\n\t"                                      \
                     "movl	%2,%%sp@-\n\t"                                      \
                     "movw	%1,%%sp@-\n\t"                                      \
                     "trap	#1\n\t"                                             \
                     "addql	#8,%%sp"                                           \
                     : "=r"(ret)                /* outputs */                  \
                     : "g"(n), "r"(_a), "r"(_b) /* inputs  */                  \
                     : "d1", "d2", "a0", "a1", "a2", "cc",                     \
                       "memory" /* clobbered regs */                           \
    );                                                                         \
    ret;                                                                       \
  })

#define trap_1_wwll(n, a, b, c)                                                \
  __extension__({                                                              \
    register long ret __asm__("d0");                                           \
    short _a = (short)(a);                                                     \
    long _b = (long)(b);                                                       \
    long _c = (long)(c);                                                       \
                                                                               \
    __asm__ volatile("movl	%4,%%sp@-\n\t"                                      \
                     "movl	%3,%%sp@-\n\t"                                      \
                     "movw	%2,%%sp@-\n\t"                                      \
                     "movw	%1,%%sp@-\n\t"                                      \
                     "trap	#1\n\t"                                             \
                     "lea	%%sp@(12),%%sp"                                      \
                     : "=r"(ret)                         /* outputs */         \
                     : "g"(n), "r"(_a), "r"(_b), "r"(_c) /* inputs  */         \
                     : "d1", "d2", "a0", "a1", "a2", "cc", "memory");          \
    ret;                                                                       \
  })
