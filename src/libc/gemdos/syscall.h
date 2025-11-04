#ifndef GEMDOS_SYSCALL_H
#define GEMDOS_SYSCALL_H

static inline long trap_1_w(short n) {
  register long retval __asm__("d0");

  __asm__ volatile("movw	%1,%%sp@-\n\t"
                   "trap	#1\n\t"
                   "addql	#2,%%sp\n\t"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n)                             /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_1_ww(short n, short a) {
  register long retval __asm__("d0");
  short _a = (short)(a);

  __asm__ volatile("movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#1\n\t"
                   "addql	#4,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a)                    /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_1_wl(short n, long a) {
  register long retval __asm__("d0");
  long _a = (long)(a);

  __asm__ volatile("movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#1\n\t"
                   "addql	#6,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a)                    /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_1_wlw(short n, long a, short b) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  short _b = (short)(b);

  __asm__ volatile("movw	%3,%%sp@-\n\t"
                   "movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#1\n\t"
                   "addql	#8,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b)           /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_1_wllw(short n, long a, long b, short c) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  long _b = (long)(b);
  short _c = (short)(c);

  __asm__ volatile("movw	%4,%%sp@-\n\t"
                   "movl	%3,%%sp@-\n\t"
                   "movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#1\n\t"
                   "lea	%%sp@(12),%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c)  /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_1_wwl(short n, short a, long b) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  long _b = (long)(b);

  __asm__ volatile("movl\t%3,%%sp@-\n\t"
                   "movw\t%2,%%sp@-\n\t"
                   "movw\t%1,%%sp@-\n\t"
                   "trap\t#1\n\t"
                   "addql\t#8,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b)           /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_1_wwlw(short n, short a, long b, short c) {
    register long retval __asm__("d0");
    short _a = (short)(a);
    long _b = (long)(b);
    short _c = (short)(c);

  __asm__ volatile("movw\t%4,%%sp@-\n\t"
                   "movl\t%3,%%sp@-\n\t"
                   "movw\t%2,%%sp@-\n\t"
                   "movw\t%1,%%sp@-\n\t"
                   "trap\t#1\n\t"
                   "lea\t%%sp@(10),%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c)  /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
    return retval;
}

static inline long trap_1_wwwl(short n, short a, short b, long c) {
    register long retval __asm__("d0");
    short _a = (short)(a);
    short _b = (short)(b);
    long _c = (long)(c);

    __asm__ volatile("movl\t%4,%%sp@-\n\t"
                     "movw\t%3,%%sp@-\n\t"
                     "movw\t%2,%%sp@-\n\t"
                     "movw\t%1,%%sp@-\n\t"
                     "trap\t#1\n\t"
                     "lea\t%%sp@(10),%%sp"
                     : "=r"(retval)                       /* outputs */
                     : "g"(n), "r"(_a), "r"(_b), "r"(_c)  /* inputs  */
                     : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                       ,
                       "memory");
    return retval;
}

static inline long trap_1_wwww(short n, short a, short b, short c) {
    register long retval __asm__("d0");
    short _a = (short)(a);
    short _b = (short)(b);
    short _c = (short)(c);

  __asm__ volatile("movw\t%4,%%sp@-\n\t"
                   "movw\t%3,%%sp@-\n\t"
                   "movw\t%2,%%sp@-\n\t"
                   "movw\t%1,%%sp@-\n\t"
                   "trap\t#1\n\t"
                   "addql\t#8,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c)  /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_1_wwll(short n, short a, long b, long c) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  long _b = (long)(b);
  long _c = (long)(c);

  __asm__ volatile("movl	%4,%%sp@-\n\t"
                   "movl	%3,%%sp@-\n\t"
                   "movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#1\n\t"
                   "lea	%%sp@(12),%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c)  /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_1_wlww(short n, long a, short b, short c) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  short _b = (short)(b);
  short _c = (short)(c);

  __asm__ volatile("movw	%4,%%sp@-\n\t"
                   "movw	%3,%%sp@-\n\t"
                   "movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#1\n\t"
                   "lea	%%sp@(10),%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c)  /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_1_wlwww(short n, long a, short b, short c, short d) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  short _b = (short)(b);
  short _c = (short)(c);
  short _d = (short)(d);

  __asm__ volatile("movw	%5,%%sp@-\n\t"
                   "movw	%4,%%sp@-\n\t"
                   "movw	%3,%%sp@-\n\t"
                   "movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#1\n\t"
                   "lea	%%sp@(12),%%sp"
                   : "=r"(retval)                               /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d) /* inputs */
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return retval;
}

static inline long trap_1_www(short n, short a, short b) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  short _b = (short)(b);

  __asm__ volatile("movw	%3,%%sp@-\n\t"
                   "movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#1\n\t"
                   "addql	#6,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b)           /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_1_wll(short n, long a, long b) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  long _b = (long)(b);

  __asm__ volatile("movl	%3,%%sp@-\n\t"
                   "movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#1\n\t"
                   "lea	%%sp@(10),%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b)           /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_1_wlll(short n, long a, long b, long c) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  long _b = (long)(b);
  long _c = (long)(c);

  __asm__ volatile("movl\t%4,%%sp@-\n\t"
                   "movl\t%3,%%sp@-\n\t"
                   "movl\t%2,%%sp@-\n\t"
                   "movw\t%1,%%sp@-\n\t"
                   "trap\t#1\n\t"
                   "lea\t%%sp@(14),%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c)  /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_1_wwlll(short n, short a, long b, long c, long d) {
    register long retval __asm__("d0");
    short _a = (short)(a);
    long _b = (long)(b);
    long _c = (long)(c);
  long _d = (long)(d);

  __asm__ volatile("movl	%5,%%sp@-\n\t"
                   "movl	%4,%%sp@-\n\t"
                   "movl	%3,%%sp@-\n\t"
                   "movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#1\n\t"
                   "lea	%%sp@(16),%%sp"
                   : "=r"(retval)                               /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d) /* inputs */
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
    return retval;
}

static inline long trap_1_wwllll(short n, short a, long b, long c, long d,
                                 long e) {
    register long retval __asm__("d0");
    short _a = (short)(a);
    long _b = (long)(b);
    long _c = (long)(c);
    long _d = (long)(d);
    long _e = (long)(e);

    __asm__ volatile("movl\t%6,%%sp@-\n\t"
                     "movl\t%5,%%sp@-\n\t"
                     "movl\t%4,%%sp@-\n\t"
                     "movl\t%3,%%sp@-\n\t"
                     "movw\t%2,%%sp@-\n\t"
                     "movw\t%1,%%sp@-\n\t"
                     "trap\t#1\n\t"
                     "lea\t%%sp@(20),%%sp"
                     : "=r"(retval) /* outputs */
                     : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d), "r"(_e)
                     : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
    return retval;
}

static inline long trap_1_wllwwl(short n, long a, long b, short c, short d,
                                 long e) {
    register long retval __asm__("d0");
  long _a = (long)(a);
  long _b = (long)(b);
  short _c = (short)(c);
  short _d = (short)(d);
  long _e = (long)(e);

  __asm__ volatile("movl\t%6,%%sp@-\n\t"
                   "movw\t%5,%%sp@-\n\t"
                   "movw\t%4,%%sp@-\n\t"
                   "movl\t%3,%%sp@-\n\t"
                   "movl\t%2,%%sp@-\n\t"
                   "movw\t%1,%%sp@-\n\t"
                   "trap\t#1\n\t"
                   "lea\t%%sp@(18),%%sp"
                   : "=r"(retval) /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d), "r"(_e)
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return retval;
}

static inline long trap_1_wwwll(short n, short a, short b, long c, long d) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  short _b = (short)(b);
  long _c = (long)(c);
  long _d = (long)(d);

  __asm__ volatile("movl	%5,%%sp@-\n\t"
                   "movl	%4,%%sp@-\n\t"
                   "movw	%3,%%sp@-\n\t"
                   "movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#1\n\t"
                   "lea	%%sp@(14),%%sp"
                   : "=r"(retval)                               /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d) /* inputs */
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return retval;
}

static inline long trap_13_wl(short n, long a) {
  register long retval __asm__("d0");
  long _a = (long)(a);

  __asm__ volatile("movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#13\n\t"
                   "addql	#6,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a)                    /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_13_w(short n) {
  register long retval __asm__("d0");

  __asm__ volatile("movw	%1,%%sp@-\n\t"
                   "trap	#13\n\t"
                   "addql	#2,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n)                             /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_13_ww(short n, short a) {
  register long retval __asm__("d0");
  short _a = (short)(a);

  __asm__ volatile("movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#13\n\t"
                   "addql	#4,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a)                    /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_13_www(short n, short a, short b) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  short _b = (short)(b);

  __asm__ volatile("movw	%3,%%sp@-\n\t"
                   "movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#13\n\t"
                   "addql	#6,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b)           /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_13_wwlwww(short n, short a, long b, short c, short d,
                                  short e) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  long _b = (long)(b);
  short _c = (short)(c);
  short _d = (short)(d);
  short _e = (short)(e);

  __asm__ volatile("movw	%6,%%sp@-\n\t"
                   "movw	%5,%%sp@-\n\t"
                   "movw	%4,%%sp@-\n\t"
                   "movl	%3,%%sp@-\n\t"
                   "movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#13\n\t"
                   "lea	%%sp@(14),%%sp"
                   : "=r"(retval) /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d),
                     "r"(_e) /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return retval;
}

static inline long trap_13_wwlwwwl(short n, short a, long b, short c, short d,
                                   short e, long f) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  long _b = (long)(b);
  short _c = (short)(c);
  short _d = (short)(d);
  short _e = (short)(e);
  long _f = (long)(f);

  __asm__ volatile("movl	%7,%%sp@-\n\t"
                   "movw	%6,%%sp@-\n\t"
                   "movw	%5,%%sp@-\n\t"
                   "movw	%4,%%sp@-\n\t"
                   "movl	%3,%%sp@-\n\t"
                   "movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#13\n\t"
                   "lea	%%sp@(18),%%sp"
                   : "=r"(retval) /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d), "r"(_e),
                     "r"(_f) /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return retval;
}

static inline long trap_13_wwl(short n, short a, long b) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  long _b = (long)(b);

  __asm__ volatile("movl	%3,%%sp@-\n\t"
                   "movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#13\n\t"
                   "addql	#8,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b)           /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_14_wwl(short n, short a, long b) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  long _b = (long)(b);

  __asm__ volatile("movl	%3,%%sp@-\n\t"
                   "movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "addql	#8,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b)           /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_14_wwll(short n, short a, long b, long c) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  long _b = (long)(b);
  long _c = (long)(c);

  __asm__ volatile("movl	%4,%%sp@-\n\t"
                   "movl	%3,%%sp@-\n\t"
                   "movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "lea	%%sp@(12),%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c)  /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_14_ww(short n, short a) {
  register long retval __asm__("d0");
  short _a = (short)(a);

  __asm__ volatile("movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "addql	#4,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a)                    /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_14_w(short n) {
  register long retval __asm__("d0");

  __asm__ volatile("movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "addql	#2,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n)                             /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_14_wllw(short n, long a, long b, short c) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  long _b = (long)(b);
  short _c = (short)(c);

  __asm__ volatile("movw	%4,%%sp@-\n\t"
                   "movl	%3,%%sp@-\n\t"
                   "movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "lea	%%sp@(12),%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c)  /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_14_wl(short n, long a) {
  register long retval __asm__("d0");
  long _a = (long)(a);

  __asm__ volatile("movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "addql	#6,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a)                    /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_14_www(short n, short a, short b) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  short _b = (short)(b);

  __asm__ volatile("movw	%3,%%sp@-\n\t"
                   "movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "addql	#6,%%sp"
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b)           /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_14_wllwwwww(short n, long a, long b, short c, short d,
                                    short e, short f, short g) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  long _b = (long)(b);
  short _c = (short)(c);
  short _d = (short)(d);
  short _e = (short)(e);
  short _f = (short)(f);
  short _g = (short)(g);

  __asm__ volatile("movw	%8,%%sp@-\n\t"
                   "movw	%7,%%sp@-\n\t"
                   "movw	%6,%%sp@-\n\t"
                   "movw	%5,%%sp@-\n\t"
                   "movw	%4,%%sp@-\n\t"
                   "movl	%3,%%sp@-\n\t"
                   "movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "lea	%%sp@(20),%%sp "
                   : "=r"(retval) /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d), "r"(_e),
                     "r"(_f), "r"(_g) /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return retval;
}

static inline long trap_14_wllwwwwlw(short n, long a, long b, short c, short d,
                                     short e, short f, long g, short h) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  long _b = (long)(b);
  short _c = (short)(c);
  short _d = (short)(d);
  short _e = (short)(e);
  short _f = (short)(f);
  long _g = (long)(g);
  short _h = (short)(h);

  __asm__ volatile("movw	%9,%%sp@-\n\t"
                   "movl	%8,%%sp@-\n\t"
                   "movw	%7,%%sp@-\n\t"
                   "movw	%6,%%sp@-\n\t"
                   "movw	%5,%%sp@-\n\t"
                   "movw	%4,%%sp@-\n\t"
                   "movl	%3,%%sp@-\n\t"
                   "movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "lea	%%sp@(24),%%sp "
                   : "=r"(retval) /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d), "r"(_e),
                     "r"(_f), "r"(_g), "r"(_h) /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return retval;
}

static inline long trap_14_wllwwwwwlw(short n, long a, long b, short c, short d,
                                      short e, short f, short g, long h,
                                      short i) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  long _b = (long)(b);
  short _c = (short)(c);
  short _d = (short)(d);
  short _e = (short)(e);
  short _f = (short)(f);
  short _g = (short)(g);
  long _h = (long)(h);
  short _i = (short)(i);

  __asm__ volatile("movw	%9,%%sp@-\n\t"
                   "movl	%8,%%sp@-\n\t"
                   "movw	%7,%%sp@-\n\t"
                   "movw	%6,%%sp@-\n\t"
                   "movw	%5,%%sp@-\n\t"
                   "movw	%4,%%sp@-\n\t"
                   "movw	%3,%%sp@-\n\t"
                   "movl	%2,%%sp@-\n\t"
                   "movl	%1,%%sp@-\n\t"
                   "movw	%0,%%sp@-"
                   : /* outputs */
                   : "g"(n), "g"(_a), "g"(_b), "g"(_c), "g"(_d), "g"(_e),
                     "g"(_f), "g"(_g), "g"(_h), "g"(_i) /* inputs  */
  );

  __asm__ volatile("trap	#14\n\t"
                   "lea	%%sp@(26),%%sp"
                   : "=r"(retval) /* outputs */
                   :              /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return retval;
}

static inline long trap_14_wwwwwww(short n, short a, short b, short c, short d,
                                   short e, short f) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  short _b = (short)(b);
  short _c = (short)(c);
  short _d = (short)(d);
  short _e = (short)(e);
  short _f = (short)(f);

  __asm__ volatile("movw	%7,%%sp@-\n\t"
                   "movw	%6,%%sp@-\n\t"
                   "movw	%5,%%sp@-\n\t"
                   "movw	%4,%%sp@-\n\t"
                   "movw	%3,%%sp@-\n\t"
                   "movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "lea	%%sp@(14),%%sp"
                   : "=r"(retval) /* outputs */
                   : "g"(n), "g"(_a), "g"(_b), "g"(_c), "g"(_d), "g"(_e),
                     "g"(_f) /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return retval;
}

static inline long trap_14_wlll(short n, long a, long b, long c) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  long _b = (long)(b);
  long _c = (long)(c);

  __asm__ volatile("movl	%4,%%sp@-\n\t"
                   "movl	%3,%%sp@-\n\t"
                   "movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "lea	%%sp@(14),%%sp "
                   : "=r"(retval)                       /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c)  /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc" /* clobbered */
                     ,
                     "memory");
  return retval;
}

static inline long trap_14_wllww(short n, long a, long b, short c, short d) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  long _b = (long)(b);
  short _c = (short)(c);
  short _d = (short)(d);

  __asm__ volatile("movw	%5,%%sp@-\n\t"
                   "movw	%4,%%sp@-\n\t"
                   "movl	%3,%%sp@-\n\t"
                   "movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "lea	%%sp@(14),%%sp"
                   : "=r"(retval)                               /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d) /* inputs */
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return retval;
}

static inline long trap_14_wwwwl(short n, short a, short b, short c, long d) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  short _b = (short)(b);
  short _c = (short)(c);
  long _d = (long)(d);

  __asm__ volatile("movl	%5,%%sp@-\n\t"
                   "movw	%4,%%sp@-\n\t"
                   "movw	%3,%%sp@-\n\t"
                   "movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "lea	%%sp@(12),%%sp "
                   : "=r"(retval)                               /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d) /* inputs */
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return retval;
}

static inline long trap_14_wwwl(short n, short a, short b, long c) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  short _b = (short)(b);
  long _c = (long)(c);

  __asm__ volatile("movl	%4,%%sp@-\n\t"
                   "movw	%3,%%sp@-\n\t"
                   "movw	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "lea	%%sp@(10),%%sp"
                   : "=r"(retval)                      /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c) /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc",
                     "memory" /* clobbered */);
  return retval;
}

static inline long trap_14_wlwlw(short n, long a, short b, long c, short d) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  short _b = (short)(b);
  long _c = (long)(c);
  short _d = (short)(d);

  __asm__ volatile("movw	%5,%%sp@-\n\t"
                   "movl	%4,%%sp@-\n\t"
                   "movw	%3,%%sp@-\n\t"
                   "movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#14\n\t"
                   "lea	%%sp@(14),%%sp"
                   : "=r"(retval)                               /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d) /* inputs */
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return retval;
}

static inline long trap_1_wlllll(short n, long a, long b, long c, long d,
                                 long e) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  long _b = (long)(b);
  long _c = (long)(c);
  long _d = (long)(d);
  long _e = (long)(e);

  __asm__ volatile("movl	%6,%%sp@-\n\t"
                   "movl	%5,%%sp@-\n\t"
                   "movl	%4,%%sp@-\n\t"
                   "movl	%3,%%sp@-\n\t"
                   "movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#1\n\t"
                   "lea	%%sp@(22),%%sp"
                   : "=r"(retval) /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d),
                     "r"(_e) /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return retval;
}

static inline long trap_1_wllllll(short n, long a, long b, long c, long d,
                                  long e, long f) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  long _b = (long)(b);
  long _c = (long)(c);
  long _d = (long)(d);
  long _e = (long)(e);
  long _f = (long)(f);

  __asm__ volatile("movl	%7,%%sp@-\n\t"
                   "movl	%6,%%sp@-\n\t"
                   "movl	%5,%%sp@-\n\t"
                   "movl	%4,%%sp@-\n\t"
                   "movl	%3,%%sp@-\n\t"
                   "movl	%2,%%sp@-\n\t"
                   "movw	%1,%%sp@-\n\t"
                   "trap	#1\n\t"
                   "lea	%%sp@(26),%%sp"
                   : "=r"(retval) /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d), "r"(_e),
                     "r"(_f) /* inputs  */
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
  return retval;
}

#endif /* GEMDOS_SYSCALL_H */
