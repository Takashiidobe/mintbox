#ifndef MINT_MINTBIND_H
#define MINT_MINTBIND_H

#include <mint/xattr.h>

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

static inline long trap_1_wlllw(short n, long a, long b, long c, short d) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  long _b = (long)(b);
  long _c = (long)(c);
  short _d = (short)(d);

  __asm__ volatile("movw\t%5,%%sp@-\n\t"
                   "movl\t%4,%%sp@-\n\t"
                   "movl\t%3,%%sp@-\n\t"
                   "movl\t%2,%%sp@-\n\t"
                   "movw\t%1,%%sp@-\n\t"
                   "trap\t#1\n\t"
                   "lea\t%%sp@(16),%%sp"
                   : "=r"(retval) /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d)
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
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

static inline long trap_1_wllll(short n, long a, long b, long c, long d) {
  register long retval __asm__("d0");
  long _a = (long)(a);
  long _b = (long)(b);
  long _c = (long)(c);
  long _d = (long)(d);

  __asm__ volatile("movl\t%5,%%sp@-\n\t"
                   "movl\t%4,%%sp@-\n\t"
                   "movl\t%3,%%sp@-\n\t"
                   "movl\t%2,%%sp@-\n\t"
                   "movw\t%1,%%sp@-\n\t"
                   "trap\t#1\n\t"
                   "lea\t%%sp@(18),%%sp"
                   : "=r"(retval) /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d)
                   : "d1", "d2", "a0", "a1", "a2", "cc", "memory");
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

static inline long trap_1_wwlllll(short n, short a, long b, long c, long d,
                                  long e, long f) {
  register long retval __asm__("d0");
  short _a = (short)(a);
  long _b = (long)(b);
  long _c = (long)(c);
  long _d = (long)(d);
  long _e = (long)(e);
  long _f = (long)(f);

  __asm__ volatile("movl\t%7,%%sp@-\n\t"
                   "movl\t%6,%%sp@-\n\t"
                   "movl\t%5,%%sp@-\n\t"
                   "movl\t%4,%%sp@-\n\t"
                   "movl\t%3,%%sp@-\n\t"
                   "movw\t%2,%%sp@-\n\t"
                   "movw\t%1,%%sp@-\n\t"
                   "trap\t#1\n\t"
                   "lea\t%%sp@(24),%%sp"
                   : "=r"(retval) /* outputs */
                   : "g"(n), "r"(_a), "r"(_b), "r"(_c), "r"(_d), "r"(_e),
                     "r"(_f)
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

#include <stdint.h>

// Getmpb - Obtain the memory parameter block information.
static inline void Getmpb(void *ptr) { (void)trap_13_wl(0x00, (long)ptr); }

// Bconstat - Test if a character is waiting on the console device.
static inline int16_t Bconstat(int16_t dev) {
  return (int16_t)trap_13_ww(0x01, dev);
}

// Bconin - Read a character from the console device.
static inline int32_t Bconin(int16_t dev) {
  return (int32_t)trap_13_ww(0x02, dev);
}

// Bconout - Write a character to the console device.
static inline int32_t Bconout(int16_t dev, int16_t c) {
  return (int32_t)trap_13_www(0x03, dev, (int16_t)(c & 0xFF));
}

// Rwabs - Raw sector I/O on a block device.
static inline int32_t Rwabs(int16_t rwflag, void *buf, int16_t n,
                            int16_t sector, int16_t dev) {
  return (int32_t)trap_13_wwlwww(0x04, rwflag, (long)buf, n, sector, dev);
}

// Lrwabs - Raw sector I/O with logical sector addressing.
static inline int32_t Lrwabs(int16_t rwflag, void *buf, int16_t n,
                             int32_t sector, int16_t dev) {
  return (int32_t)trap_13_wwlwwwl(0x04, rwflag, (long)buf, n, -1, dev,
                                  (long)sector);
}

// Setexc - Install an exception vector handler.
static inline void (*Setexc(int16_t vnum, void (*vptr)(void)))(void) {
  return (void (*)(void))trap_13_wwl(0x05, vnum, (long)vptr);
}

// Tickcal - Return the configured tick calibration value.
static inline int32_t Tickcal(void) { return (int32_t)trap_13_w(0x06); }

// Getbpb - Fetch the BIOS parameter block for a drive.
static inline void *Getbpb(int16_t dev) {
  return (void *)trap_13_ww(0x07, dev);
}

// Bcostat - Test if a character is waiting on the auxiliary console.
static inline int16_t Bcostat(int16_t dev) {
  return (int16_t)trap_13_ww(0x08, dev);
}

// Mediach - Report media change status for a drive.
static inline int16_t Mediach(int16_t dev) {
  return (int16_t)trap_13_ww(0x09, dev);
}

// Drvmap - Return a bitmap of currently mounted drives.
static inline int32_t Drvmap(void) { return (int32_t)trap_13_w(0x0A); }

// Kbshift - Read or set the keyboard shift state.
static inline int32_t Kbshift(int16_t data) {
  return (int32_t)trap_13_ww(0x0B, data);
}

// Getshift - Read the current keyboard shift state.
static inline int32_t Getshift(void) { return Kbshift(-1); }

// Cauxin - Input via serial port.
static inline int32_t Cauxin(void) { return (int32_t)trap_1_w(0x03); }

// Cauxis - Check the input status of the serial port.
static inline int16_t Cauxis(void) { return (int16_t)trap_1_w(0x12); }

// Cauxos - Check the output status of the serial port.
static inline int16_t Cauxos(void) { return (int16_t)trap_1_w(0x13); }

// Cauxout - Write a character to the serial port.
static inline int32_t Cauxout(int16_t c) { return (int32_t)trap_1_ww(0x04, c); }

// Cconin - Read a character from the standard input device.
static inline int32_t Cconin(void) { return (int32_t)trap_1_w(0x01); }

// Cconis - Check whether a character is waiting in the input buffer.
static inline int32_t Cconis(void) { return (int32_t)trap_1_w(0x0B); }

// Cconos - Check status of the standard output device.
static inline int16_t Cconos(void) { return (int16_t)trap_1_w(0x10); }

// Cconout - Write a character to the standard output device.
static inline int32_t Cconout(int16_t c) { return (int32_t)trap_1_ww(0x02, c); }

// Cconrs - Read a string from the standard input.
static inline int32_t Cconrs(void *buf) {
  return (int32_t)trap_1_wl(0x0A, (long)buf);
}

// Cconws - Write a string to the standard output device.
static inline int32_t Cconws(const int8_t *buf) {
  return (int32_t)trap_1_wl(0x09, (long)buf);
}

// Cnecin - Read a character without echo.
static inline int32_t Cnecin(void) { return (int32_t)trap_1_w(0x08); }

// Cprnos - Check the status of the printer port.
static inline int16_t Cprnos(void) { return (int16_t)trap_1_w(0x11); }

// Cprnout - Write a character to the printer port.
static inline int32_t Cprnout(int16_t c) { return (int32_t)trap_1_ww(0x05, c); }

// Crawcin - Read an unbuffered character from standard input device.
static inline int32_t Crawcin(void) { return (int32_t)trap_1_w(0x07); }

// Crawio - Permit unbuffered input/output.
static inline int32_t Crawio(int16_t w) { return (int32_t)trap_1_ww(0x06, w); }

#include <stdint.h>

/* Forward declarations for GEMDOS structures provided elsewhere. */
typedef struct DISKINFO DISKINFO;

// Dchroot - Change the root directory for the calling process.
static inline int32_t Dchroot(const char *path) {
  return (int32_t)trap_1_wl(0x14A, (long)path);
}

// Dclosedir - Close a specified directory.
static inline int32_t Dclosedir(int32_t dirhandle) {
  return (int32_t)trap_1_wl(0x12B, (long)dirhandle);
}

// Dcntl - Execute a file-system-specific operation on a file or directory.
static inline int32_t Dcntl(int16_t cmd, int8_t *name, int32_t arg) {
  return (int32_t)trap_1_wwll(0x130, cmd, (long)name, (long)arg);
}

// Dcreate - Create a directory.
static inline int32_t Dcreate(const char *path) {
  return (int32_t)trap_1_wl(0x39, (long)path);
}

// Ddelete - Delete a directory.
static inline int32_t Ddelete(const char *path) {
  return (int32_t)trap_1_wl(0x3A, (long)path);
}

// Dfree - Obtain free and total capacity of a drive.
static inline int16_t Dfree(DISKINFO *buf, int16_t driveno) {
  return (int16_t)trap_1_wlw(0x36, (long)buf, driveno);
}

// Dgetcwd - Obtain the current directory of a process.
static inline int32_t Dgetcwd(int8_t *path, int16_t drv, int16_t size) {
  return (int32_t)trap_1_wlww(0x13B, (long)path, drv, size);
}

// Dgetdrv - Obtain the current drive.
static inline int16_t Dgetdrv(void) { return (int16_t)trap_1_w(0x19); }

// Dgetpath - Obtain current path specification.
static inline int16_t Dgetpath(int8_t *path, int16_t driveno) {
  return (int16_t)trap_1_wlw(0x47, (long)path, driveno);
}

// Dlock - Lock a BIOS device or release it again.
static inline int32_t Dlock(int16_t mode, int16_t drv) {
  return (int32_t)trap_1_www(0x135, mode, drv);
}

// Dopendir - Open a specified directory for reading.
static inline int32_t Dopendir(int8_t *name, int16_t flag) {
  return (int32_t)trap_1_wlw(0x128, (long)name, flag);
}

// Dpathconf - Obtain information about a file-system.
static inline int32_t Dpathconf(int8_t *name, int16_t mode) {
  return (int32_t)trap_1_wlw(0x124, (long)name, mode);
}

// Dreaddir - Read directory information.
static inline int32_t Dreaddir(int16_t len, int32_t dirhandle, int8_t *buf) {
  return (int32_t)trap_1_wwll(0x129, len, (long)dirhandle, (long)buf);
}

// Dreadlabel - Read file-system label.
static inline int32_t Dreadlabel(const char *path, int8_t *label,
                                 int16_t length) {
  return (int32_t)trap_1_wllw(0x152, (long)path, (long)label, length);
}

// Drewinddir - Rewind the specified directory to the first entry.
static inline int32_t Drewinddir(int32_t handle) {
  return (int32_t)trap_1_wl(0x12A, (long)handle);
}

// Dsetdrv - Set the current drive and return a bitmap of mounted drives.
static inline int32_t Dsetdrv(int16_t drv) {
  return (int32_t)trap_1_ww(0x0E, drv);
}

// Dsetkey - Set the key/passphrase for a drive.
static inline int32_t Dsetkey(int32_t hidev, int32_t lowdev, int8_t *key,
                              int16_t cipher) {
  return (int32_t)trap_1_wlllw(0x14D, (long)hidev, (long)lowdev, (long)key,
                               cipher);
}

// Dsetpath - Set the current directory.
static inline int16_t Dsetpath(const char *path) {
  return (int16_t)trap_1_wl(0x3B, (long)path);
}

// Dwritelabel - Set file-system label.
static inline int32_t Dwritelabel(const char *path, const char *label) {
  return (int32_t)trap_1_wll(0x153, (long)path, (long)label);
}

// Dxopendir - Open directory for reading.
static inline int32_t Dxopendir(int8_t *name, int16_t flag) {
  return (int32_t)trap_1_wlw(0x510, (long)name, flag);
}

// Dxreaddir - Read directory information and obtain attributes.
static inline int32_t Dxreaddir(int16_t ln, int32_t dirh, int8_t *buf,
                                XATTR *xattr, int32_t *xr) {
  return (int32_t)trap_1_wwllll(0x142, ln, (long)dirh, (long)buf, (long)xattr,
                                (long)xr);
}

/* Forward declarations for GEMDOS structures provided elsewhere. */
typedef struct DOSTIME DOSTIME;
typedef struct DTA DTA;
typedef struct STAT STAT;
typedef struct POLLFD POLLFD;

/* Fattrib - Obtain or change file attributes. */
static inline int16_t Fattrib(const char *filename, int16_t wflag,
                              int16_t attrib) {
  return (int16_t)trap_1_wlww(0x43, (long)filename, wflag, attrib);
}

/* Fchmod - Change file access mode bits. */
static inline int32_t Fchmod(char *name, int16_t mode) {
  return (int32_t)trap_1_wlw(0x132, (long)name, mode);
}

/* Fchown - Change file ownership. */
static inline int32_t Fchown(char *name, int16_t uid, int16_t gid) {
  return (int32_t)trap_1_wlww(0x131, (long)name, uid, gid);
}

/* Fchown16 - Change file ownership with follow flag. */
static inline int32_t Fchown16(char *name, int16_t uid, int16_t gid,
                               int16_t flag) {
  return (int32_t)trap_1_wlwww(0x180, (long)name, uid, gid, flag);
}

/* Fchdir - Change the current directory using a handle. */
static inline int32_t Fchdir(int16_t handle) {
  return (int32_t)trap_1_ww(0x181, handle);
}

/* Fcntl - Control operations on file descriptors. */
static inline int32_t Fcntl(int16_t fh, int32_t arg, int16_t cmd) {
  return (int32_t)trap_1_wwlw(0x104, fh, (long)arg, cmd);
}

/* Fcreate - Create a file. */
static inline int16_t Fcreate(const char *fname, int16_t attr) {
  return (int16_t)trap_1_wlw(0x3C, (long)fname, attr);
}

/* Fdatime - Get or set the date/time stamp for a file handle. */
static inline void Fdatime(DOSTIME *timeptr, int16_t handle, int16_t wflag) {
  (void)trap_1_wlww(0x57, (long)timeptr, handle, wflag);
}

/* Fdelete - Remove a file. */
static inline int32_t Fdelete(const char *fname) {
  return (int32_t)trap_1_wl(0x41, (long)fname);
}

/* Fopen - Open a file. */
static inline int32_t Fopen(const char *fname, int16_t mode) {
  return (int32_t)trap_1_wlw(0x3D, (long)fname, mode);
}

/* Fclose - Close an open file handle. */
static inline int32_t Fclose(int16_t handle) {
  return (int32_t)trap_1_ww(0x3E, handle);
}

/* Fread - Read bytes from a file handle. */
static inline int32_t Fread(int16_t handle, int32_t count, const void *buf) {
  return (int32_t)trap_1_wwll(0x3F, handle, (long)count, (long)buf);
}

/* Fwrite - Write bytes to a file handle. */
static inline int32_t Fwrite(int16_t handle, int32_t count, const void *buf) {
  return (int32_t)trap_1_wwll(0x40, handle, (long)count, (long)buf);
}

/* Fdirfd - Obtain directory file descriptor. */
static inline int16_t Fdirfd(int32_t handle) {
  return (int16_t)trap_1_wl(0x183, (long)handle);
}

/* Fdup - Duplicate a file handle. */
static inline int16_t Fdup(int16_t handle) {
  return (int16_t)trap_1_ww(0x45, handle);
}

/* Ffchmod - Change mode of a file descriptor. */
static inline int32_t Ffchmod(int16_t fd, int16_t mode) {
  return (int32_t)trap_1_www(0x102, fd, mode);
}

/* Ffchown - Change ownership of a file descriptor. */
static inline int32_t Ffchown(int16_t fd, int16_t uid, int16_t gid) {
  return (int32_t)trap_1_wwww(0x101, fd, uid, gid);
}

/* Ffdopendir - Open a directory stream using a file descriptor. */
static inline int32_t Ffdopendir(int16_t fd) {
  return (int32_t)trap_1_ww(0x182, fd);
}

/* Fforce - Force a file handle to standard handle. */
static inline int16_t Fforce(int16_t stdh, int16_t nonstdh) {
  return (int16_t)trap_1_www(0x46, stdh, nonstdh);
}

/* Ffstat64 - Obtain 64-bit file status for a descriptor. */
static inline int32_t Ffstat64(int16_t fd, STAT *stat) {
  return (int32_t)trap_1_wwl(0x15D, fd, (long)stat);
}

/* Fgetchar - Read a character from a device or file. */
static inline int32_t Fgetchar(int16_t fh, int16_t mode) {
  return (int32_t)trap_1_www(0x107, fh, mode);
}

/* Fgetdta - Retrieve pointer to the default DTA. */
static inline DTA *Fgetdta(void) { return (DTA *)trap_1_w(0x2F); }

/* Finstat - Test input status of a handle. */
static inline int32_t Finstat(int16_t fh) {
  return (int32_t)trap_1_ww(0x105, fh);
}

/* Flink - Create a hard link. */
static inline int32_t Flink(char *oldname, int8_t *newname) {
  return (int32_t)trap_1_wll(0x12D, (long)oldname, (long)newname);
}

/* Flock - Protect a region of a file. */
static inline int32_t Flock(int16_t handle, int16_t mode, int32_t start,
                            int32_t length) {
  return (int32_t)trap_1_wwwll(0x5C, handle, mode, (long)start, (long)length);
}

/* Fmidipipe - Create a MIDI pipe. */
static inline int32_t Fmidipipe(int16_t pid, int16_t in, int16_t out) {
  return (int32_t)trap_1_wwww(0x126, pid, in, out);
}

/* Foutstat - Test output status of a handle. */
static inline int32_t Foutstat(int16_t fh) {
  return (int32_t)trap_1_ww(0x106, fh);
}

/* Fpipe - Create an unnamed pipe. */
static inline int32_t Fpipe(int16_t usrh[2]) {
  return (int32_t)trap_1_wl(0x100, (long)usrh);
}

/* Fpoll - Poll file descriptors. */
static inline int32_t Fpoll(POLLFD *fds, uint32_t nfds, uint32_t timeout) {
  return (int32_t)trap_1_wlll(0x15A, (long)fds, (long)nfds, (long)timeout);
}

/* Fputchar - Write a character to a device or file. */
static inline int32_t Fputchar(int16_t fh, int32_t ch, int16_t mode) {
  return (int32_t)trap_1_wwlw(0x108, fh, (long)ch, mode);
}

/* Freadlink - Read a symbolic link. */
static inline int32_t Freadlink(int16_t bufsiz, char *buf, int8_t *name) {
  return (int32_t)trap_1_wwll(0x12F, bufsiz, (long)buf, (long)name);
}

/* Frename - Rename a file. */
static inline int32_t Frename(const char *oldname, const char *newname) {
  return (int32_t)trap_1_wwll(0x56, 0, (long)oldname, (long)newname);
}

/* Fseek - Seek within a file. */
static inline int32_t Fseek(int32_t offset, int16_t handle, int16_t seekmode) {
  return (int32_t)trap_1_wlww(0x42, (long)offset, handle, seekmode);
}

/* Fseek64 - Seek within a file using 64-bit offsets. */
static inline int32_t Fseek64(int32_t hioffset, uint32_t lowoffset,
                              int16_t handle, int16_t seekmode,
                              int64_t *newpos) {
  return (int32_t)trap_1_wllwwl(0x14C, (long)hioffset, (long)lowoffset, handle,
                                seekmode, (long)newpos);
}

/* Fselect - Select on file descriptors. */
static inline int32_t Fselect(uint16_t timeout, int32_t *rfds, int32_t *wfds,
                              int32_t *xfds) {
  return (int32_t)trap_1_wwlll(0x11D, timeout, (long)rfds, (long)wfds,
                               (long)xfds);
}

/* Fsetdta - Set the default DTA pointer. */
static inline void Fsetdta(DTA *buf) { (void)trap_1_wl(0x1A, (long)buf); }

/* Fsfirst - Initiate a file search. */
static inline int32_t Fsfirst(const char *filename, int16_t attr) {
  return (int32_t)trap_1_wlw(0x4E, (long)filename, attr);
}

/* Fsnext - Continue a file search. */
static inline int16_t Fsnext(void) { return (int16_t)trap_1_w(0x4F); }

/* Fsymlink - Create a symbolic link. */
static inline int32_t Fsymlink(char *oldname, char *newname) {
  return (int32_t)trap_1_wll(0x12E, (long)oldname, (long)newname);
}

/* Fstat64 - Obtain 64-bit file status information. */
static inline int32_t Fstat64(int16_t flag, char *name, STAT *stat) {
  return (int32_t)trap_1_wwll(0x14B, flag, (long)name, (long)stat);
}

/* Fsync - Synchronize a file's in-core state with storage. */
static inline int16_t Fsync(int16_t handle) {
  return (int16_t)trap_1_ww(0x103, handle);
}

/* Fxattr - Get or set extended file attributes. */
static inline int32_t Fxattr(int16_t flag, char *name, XATTR *xattr) {
  return (int32_t)trap_1_wwll(0x12C, flag, (long)name, (long)xattr);
}

/* Forward declarations for networking structures supplied elsewhere. */
struct iovec;
struct msghdr;
struct sockaddr;

// Fwritev - Write data from multiple buffers.
static inline int32_t Fwritev(int16_t handle, struct iovec *iov, int32_t niov) {
  return (int32_t)trap_1_wwll(0x15B, handle, (long)iov, (long)niov);
}

// Freadv - Read data into multiple buffers.
static inline int32_t Freadv(int16_t handle, struct iovec *iov, int32_t niov) {
  return (int32_t)trap_1_wwll(0x15C, handle, (long)iov, (long)niov);
}

// Fsocket - Create an endpoint for communication.
static inline int32_t Fsocket(int32_t domain, int32_t type, int32_t protocol) {
  return (int32_t)trap_1_wlll(0x160, (long)domain, (long)type, (long)protocol);
}

// Fsocketpair - Create a pair of connected sockets.
static inline int32_t Fsocketpair(int32_t domain, int32_t type,
                                  int32_t protocol, int16_t fds[2]) {
  return (int32_t)trap_1_wllll(0x161, (long)domain, (long)type, (long)protocol,
                               (long)fds);
}

// Faccept - Accept a connection on a socket.
static inline int32_t Faccept(int16_t fd, struct sockaddr *name,
                              uint32_t *anamelen) {
  return (int32_t)trap_1_wwll(0x162, fd, (long)name, (long)anamelen);
}

// Fconnect - Initiate a connection on a socket.
static inline int32_t Fconnect(int16_t fd, struct sockaddr *name,
                               uint32_t anamelen) {
  return (int32_t)trap_1_wwll(0x163, fd, (long)name, (long)anamelen);
}

// Fbind - Bind a name to a socket.
static inline int32_t Fbind(int16_t fd, const struct sockaddr *name,
                            uint32_t anamelen) {
  return (int32_t)trap_1_wwll(0x164, fd, (long)name, (long)anamelen);
}

// Flisten - Listen for connections on a socket.
static inline int32_t Flisten(int16_t fd, int32_t backlog) {
  return (int32_t)trap_1_wwl(0x165, fd, (long)backlog);
}

// Frecvmsg - Receive a message from a socket.
static inline int32_t Frecvmsg(int16_t fd, struct msghdr *msg, int32_t flags) {
  return (int32_t)trap_1_wwll(0x166, fd, (long)msg, (long)flags);
}

// Fsendmsg - Send a message on a socket.
static inline int32_t Fsendmsg(int16_t fd, const struct msghdr *msg,
                               int32_t flags) {
  return (int32_t)trap_1_wwll(0x167, fd, (long)msg, (long)flags);
}

// Frecvfrom - Receive a message from a socket.
static inline int32_t Frecvfrom(int16_t fd, void *buf, int32_t buflen,
                                int32_t flags, struct sockaddr *to,
                                uint32_t *addrlen) {
  return (int32_t)trap_1_wwlllll(0x168, fd, (long)buf, (long)buflen,
                                 (long)flags, (long)to, (long)addrlen);
}

// Fsendto - Send a message on a socket.
static inline int32_t Fsendto(int16_t fd, const void *buf, int32_t buflen,
                              int32_t flags, const struct sockaddr *to,
                              uint32_t addrlen) {
  return (int32_t)trap_1_wwlllll(0x169, fd, (long)buf, (long)buflen,
                                 (long)flags, (long)to, (long)addrlen);
}

// Fsetsockopt - Set options on sockets.
static inline int32_t Fsetsockopt(int16_t fd, int32_t level, int32_t name,
                                  const void *val, uint32_t valsize) {
  return (int32_t)trap_1_wwllll(0x16A, fd, (long)level, (long)name, (long)val,
                                (long)valsize);
}

// Fgetsockopt - Get options on sockets.
static inline int32_t Fgetsockopt(int16_t fd, int32_t level, int32_t name,
                                  void *val, uint32_t *valsize) {
  return (int32_t)trap_1_wwllll(0x16B, fd, (long)level, (long)name, (long)val,
                                (long)valsize);
}

// Fgetpeername - Get name of connected peer socket.
static inline int32_t Fgetpeername(int16_t fd, struct sockaddr *asa,
                                   uint32_t *alen) {
  return (int32_t)trap_1_wwll(0x16C, fd, (long)asa, (long)alen);
}

// Fgetsockname - Get socket name.
static inline int32_t Fgetsockname(int16_t fd, struct sockaddr *asa,
                                   uint32_t *alen) {
  return (int32_t)trap_1_wwll(0x16D, fd, (long)asa, (long)alen);
}

// Fshutdown - Shut down part of a full-duplex connection.
static inline int32_t Fshutdown(int16_t fd, int32_t how) {
  return (int32_t)trap_1_wwl(0x16E, fd, (long)how);
}

/* Forward declarations for SysV IPC structures. */
typedef struct msqid_ds msqid_ds;
typedef struct sembuf sembuf;
typedef struct shmid_ds shmid_ds;

// Pshmget - Obtain a shared memory segment identifier.
static inline int32_t Pshmget(int32_t key, int32_t size, int32_t shmflg) {
  return (int32_t)trap_1_wlll(0x170, (long)key, (long)size, (long)shmflg);
}

// Pshmctl - Control operations on a shared memory segment.
static inline int32_t Pshmctl(int32_t shmid, int32_t cmd, shmid_ds *buf) {
  return (int32_t)trap_1_wlll(0x171, (long)shmid, (long)cmd, (long)buf);
}

// Pshmat - Attach a shared memory segment.
static inline void *Pshmat(int32_t shmid, void *shmaddr, int32_t shmflg) {
  return (void *)trap_1_wlll(0x172, (long)shmid, (long)shmaddr, (long)shmflg);
}

// Pshmdt - Detach a shared memory segment.
static inline int32_t Pshmdt(void *shmaddr) {
  return (int32_t)trap_1_wl(0x173, (long)shmaddr);
}

// Psemget - Obtain a semaphore set identifier.
static inline int32_t Psemget(int32_t key, int32_t nsems, int32_t semflg) {
  return (int32_t)trap_1_wlll(0x174, (long)key, (long)nsems, (long)semflg);
}

// Psemctl - Control operations on a semaphore set.
static inline int32_t Psemctl(int32_t semid, int32_t semnum, int32_t cmd,
                              intptr_t arg) {
  return (int32_t)trap_1_wllll(0x175, (long)semid, (long)semnum, (long)cmd,
                               (long)arg);
}

// Psemop - Perform an array of semaphore operations.
static inline int32_t Psemop(int32_t semid, sembuf *sops, int32_t nsops) {
  return (int32_t)trap_1_wlll(0x176, (long)semid, (long)sops, (long)nsops);
}

// Psemconfig - Configure system-wide semaphore limits.
static inline int32_t Psemconfig(int32_t flag) {
  return (int32_t)trap_1_wl(0x177, (long)flag);
}

// Pmsgget - Obtain a message queue identifier.
static inline int32_t Pmsgget(int32_t key, int32_t msgflg) {
  return (int32_t)trap_1_wll(0x178, (long)key, (long)msgflg);
}

// Pmsgctl - Control operations on a message queue.
static inline int32_t Pmsgctl(int32_t msqid, int32_t cmd, msqid_ds *buf) {
  return (int32_t)trap_1_wlll(0x179, (long)msqid, (long)cmd, (long)buf);
}

// Pmsgsnd - Send a message to a queue.
static inline int32_t Pmsgsnd(int32_t msqid, const void *msgp, int32_t msgsz,
                              int32_t msgflg) {
  return (int32_t)trap_1_wllll(0x17A, (long)msqid, (long)msgp, (long)msgsz,
                               (long)msgflg);
}

// Pmsgrcv - Receive a message from a queue.
static inline int32_t Pmsgrcv(int32_t msqid, void *msgp, int32_t msgsz,
                              int32_t msgtyp, int32_t msgflg) {
  return (int32_t)trap_1_wlllll(0x17B, (long)msqid, (long)msgp, (long)msgsz,
                                (long)msgtyp, (long)msgflg);
}

/* Maccess - verify accessibility of a region of memory. */
static inline int32_t Maccess(void *start, int32_t size, int16_t mode) {
  return (int32_t)trap_1_wllw(0x17D, (long)start, (long)size, mode);
}

/* Maddalt - Register 'Alternative' RAM with GEMDOS. */
static inline int32_t Maddalt(void *start, int32_t size) {
  return (int32_t)trap_1_wll(0x14, (long)start, (long)size);
}

/* Malloc - Reserve a block of memory or inquire free memory. */
static inline void *Malloc(int32_t number) {
  return (void *)trap_1_wl(0x48, (long)number);
}

/* Mfree - Release a block of memory. */
static inline int32_t Mfree(void *block) {
  return (int32_t)trap_1_wl(0x49, (long)block);
}

/* Mshrink - Reduce or enlarge a memory block. */
static inline int32_t Mshrink(void *block, int32_t newsiz) {
  return (int32_t)trap_1_wwll(0x4A, (int16_t)0, (long)block, (long)newsiz);
}

/* Mvalidate - verify access to a process memory region. */
static inline int32_t Mvalidate(int16_t pid, void *start, int32_t size,
                                int32_t *flags) {
  return (int32_t)trap_1_wwlll(0x141, pid, (long)start, (long)size,
                               (long)flags);
}

/* Mxalloc - Reserve memory according to specified preferences. */
static inline void *Mxalloc(int32_t amount, int16_t mode) {
  return (void *)trap_1_wlw(0x44, (long)amount, mode);
}

/* Fflush - Flush the buffer of a file. */
static inline int32_t Fflush(int16_t handle) {
  return (int32_t)trap_1_ww(0x66, handle);
}

/* Frlock - Protect a portion of a file. */
static inline int32_t Frlock(int16_t handle, int32_t start, int32_t length) {
  return (int32_t)trap_1_wwll(0x62, handle, (long)start, (long)length);
}

/* Frunlock - Unlock a portion of a file. */
static inline int32_t Frunlock(int16_t handle, int32_t start) {
  return (int32_t)trap_1_wwl(0x63, handle, (long)start);
}

/* Funlock - Unlock a portion of a file. */
static inline int32_t Funlock(int16_t handle) {
  return (int32_t)trap_1_ww(0x65, handle);
}

/* Nversion - Network identifier determine. */
static inline int32_t Nversion(void) { return (int32_t)trap_1_w(0x60); }

// Forward declarations for structures supplied elsewhere.
struct sigaction;

// Pause - Suspend a process until the arrival of a signal.
static inline void Pause(void) { (void)trap_1_w(0x121); }

// Pdomain - Set or get the caller's execution domain.
static inline int16_t Pdomain(int16_t dom) {
  return (int16_t)trap_1_ww(0x119, dom);
}

// Pexec - Load and execute a program.
static inline int32_t Pexec(uint16_t mode, const int8_t *fname,
                            const void *cmdline, const void *env) {
  return (int32_t)trap_1_wwlll(0x4B, (int16_t)mode, (long)fname, (long)cmdline,
                               (long)env);
}

// Pfork - Create a copy of the current process.
static inline int16_t Pfork(void) { return (int16_t)trap_1_w(0x11B); }

// Pgetauid - Get user ID of a process at the start.
static inline int16_t Pgetauid(void) { return (int16_t)trap_1_w(0x145); }

// Pgetegid - Get effective group ID of a process.
static inline int32_t Pgetegid(void) { return (int32_t)trap_1_w(0x139); }

// Pgeteuid - Get effective user ID of a process.
static inline int32_t Pgeteuid(void) { return (int32_t)trap_1_w(0x138); }

// Pgetgid - Get group ID of a process.
static inline int16_t Pgetgid(void) { return (int16_t)trap_1_w(0x114); }

// Pgetgroups - Get supplementary group IDs for the calling process.
static inline int32_t Pgetgroups(int16_t len, int16_t *gidset) {
  return (int32_t)trap_1_wwl(0x147, len, (long)gidset);
}

// Pgetpgrp - Get current group number.
static inline int16_t Pgetpgrp(void) { return (int16_t)trap_1_w(0x10D); }

// Pgetpid - Get current process ID.
static inline int16_t Pgetpid(void) { return (int16_t)trap_1_w(0x10B); }

// Pgetppid - Get parent process ID.
static inline int16_t Pgetppid(void) { return (int16_t)trap_1_w(0x10C); }

// Pgetpriority - Get the current priority value for a process.
static inline int32_t Pgetpriority(int16_t which, int16_t who) {
  return (int32_t)trap_1_www(0x158, which, who);
}

// Pgetuid - Get user ID of a process.
static inline int16_t Pgetuid(void) { return (int16_t)trap_1_w(0x10F); }

// Pkill - Send a signal to one or more processes.
static inline int32_t Pkill(int16_t pid, int16_t sig) {
  return (int32_t)trap_1_www(0x111, pid, sig);
}

// Pmsg - Send and receive messages.
static inline int32_t Pmsg(int16_t mode, int32_t mbox, void *msg) {
  return (int32_t)trap_1_wwll(0x125, mode, (long)mbox, (long)msg);
}

// Pnice - Alter priority of the calling process.
static inline int16_t Pnice(int16_t delta) {
  return (int16_t)trap_1_ww(0x10A, delta);
}

// Prenice - Adjust priority of a specified process.
static inline int32_t Prenice(int16_t pid, int16_t delta) {
  return (int32_t)trap_1_www(0x127, pid, delta);
}

// Prusage - Obtain resource information about current process.
static inline int32_t Prusage(int32_t *r) {
  return (int32_t)trap_1_wl(0x11E, (long)r);
}

// Psemaphore - Create, use or destroy a semaphore.
static inline int32_t Psemaphore(int16_t mode, int32_t id, int32_t timeout) {
  return (int32_t)trap_1_wwll(0x134, mode, (long)id, (long)timeout);
}

// Psetauid - Set user ID of a process at the start.
static inline int16_t Psetauid(int16_t id) {
  return (int16_t)trap_1_ww(0x146, id);
}

// Psetegid - Set the effective group ID for the calling process.
static inline int32_t Psetegid(int16_t egid) {
  return (int32_t)trap_1_ww(0x144, egid);
}

// Pseteuid - Set the effective user ID for the calling process.
static inline int32_t Pseteuid(int16_t euid) {
  return (int32_t)trap_1_ww(0x143, euid);
}

// Psetgid - Alter the group ID of the calling process.
static inline int16_t Psetgid(int16_t id) {
  return (int16_t)trap_1_ww(0x115, id);
}

// Psetgroups - Set supplementary group IDs for the calling process.
static inline int32_t Psetgroups(int16_t len, const int16_t *gidset) {
  return (int32_t)trap_1_wwl(0x148, len, (long)gidset);
}

// Psetlimit - Set or obtain allocation limits of system resources.
static inline int32_t Psetlimit(int16_t lim, int32_t value) {
  return (int32_t)trap_1_wwl(0x11F, lim, (long)value);
}

// Psetpgrp - Get or set process group number of a process.
static inline int16_t Psetpgrp(int16_t pid, int16_t newgrp) {
  return (int16_t)trap_1_www(0x10E, pid, newgrp);
}

// Psetpriority - Set the current priority value for a process.
static inline int32_t Psetpriority(int16_t which, int16_t who, int16_t pri) {
  return (int32_t)trap_1_wwww(0x159, which, who, pri);
}

// Psetregid - Set the real and/or effective group ID for the calling process.
static inline int32_t Psetregid(int16_t rgid, int16_t egid) {
  return (int32_t)trap_1_www(0x14F, rgid, egid);
}

// Psetreuid - Set the real and/or effective user ID for the calling process.
static inline int32_t Psetreuid(int16_t ruid, int16_t euid) {
  return (int32_t)trap_1_www(0x14E, ruid, euid);
}

// Psetuid - Alter the user ID of a process.
static inline int16_t Psetuid(int16_t id) {
  return (int16_t)trap_1_ww(0x110, id);
}

// Psigaction - Set default action for a specified signal.
static inline int32_t Psigaction(int16_t sig, struct sigaction *act,
                                 struct sigaction *oact) {
  return (int32_t)trap_1_wwll(0x137, sig, (long)act, (long)oact);
}

// Psigblock - Alter signal mask.
static inline int32_t Psigblock(int32_t mask) {
  return (int32_t)trap_1_wl(0x116, (long)mask);
}

// Psigintr - Assign a signal to a particular exception vector.
static inline int32_t Psigintr(int16_t vec, int16_t sig) {
  return (int32_t)trap_1_www(0x13E, vec, sig);
}

// Psignal - Alter manner of signal handling.
static inline int32_t Psignal(int16_t sig, int32_t handler) {
  return (int32_t)trap_1_wwl(0x112, sig, (long)handler);
}

// Psigpause - Suspend process until the arrival of a signal.
static inline void Psigpause(int32_t mask) {
  (void)trap_1_wl(0x136, (long)mask);
}

// Psigpending - Check which signals have been sent but not processed.
static inline int32_t Psigpending(void) { return (int32_t)trap_1_w(0x123); }

// Psigreturn - Prepare exit from a signal handler.
static inline void Psigreturn(void) { (void)trap_1_w(0x11A); }

// Psigsetmask - Set or replace a signal mask.
static inline int32_t Psigsetmask(int32_t mask) {
  return (int32_t)trap_1_wl(0x117, (long)mask);
}

// Psysctl - Get or set system information.
static inline int32_t Psysctl(int32_t *name, uint32_t namelen, void *oldbuf,
                              uint32_t *oldlenp, void *newbuf,
                              uint32_t newlen) {
  return (int32_t)trap_1_wllllll(0x15E, (long)name, (long)namelen, (long)oldbuf,
                                 (long)oldlenp, (long)newbuf, (long)newlen);
}

// Pterm - Terminate a TOS program.
static inline void Pterm(uint16_t retcode) {
  (void)trap_1_ww(0x4C, (int16_t)retcode);
}

// Pterm0 - Terminate a TOS program and return 0 to caller.
static inline void Pterm0(void) { (void)trap_1_w(0x00); }

// Ptermres - Terminate a program but leave it resident.
static inline void Ptermres(int32_t keepcnt, int16_t retcode) {
  (void)trap_1_wlw(0x31, (long)keepcnt, retcode);
}

// Ptrace - Process tracing and debugging.
static inline int16_t Ptrace(int16_t request, int16_t pid, void *addr,
                             int32_t data) {
  return (int16_t)trap_1_wwwll(0x140, request, pid, (long)addr, (long)data);
}

// Pumask - Set initial creation mask for files and directories.
static inline int16_t Pumask(int16_t mode) {
  return (int16_t)trap_1_ww(0x133, mode);
}

// Pusrval - Set or query process specific information.
static inline int32_t Pusrval(int32_t val) {
  return (int32_t)trap_1_wl(0x118, (long)val);
}

// Pvfork - Create a copy of the current process.
static inline int16_t Pvfork(void) { return (int16_t)trap_1_w(0x113); }

// Pwait - Obtain the exit code of a waiting or terminated child process.
static inline int32_t Pwait(void) { return (int32_t)trap_1_w(0x109); }

// Pwait3 - Get exit code information about child processes.
static inline int32_t Pwait3(int16_t flag, int32_t *rusage) {
  return (int32_t)trap_1_wwl(0x11C, flag, (long)rusage);
}

// Pwaitpid - Get exit code information about specific child processes.
static inline int32_t Pwaitpid(int16_t pid, int16_t flag, int32_t *rusage) {
  return (int32_t)trap_1_wwwl(0x13A, pid, flag, (long)rusage);
}

// Forward declarations for structures supplied elsewhere.
typedef struct COOKIE COOKIE;
typedef struct SHARED_LIB SHARED_LIB;
typedef struct SLB_EXEC SLB_EXEC;

// Salert - Output alert or error-message.
static inline void Salert(int8_t *msg) { (void)trap_1_wl(0x13C, (long)msg); }

// Sconfig - Configuration of parts of the operating system.
static inline int32_t Sconfig(int16_t mode, int32_t flags) {
  return (int32_t)trap_1_wwl(0x33, mode, (long)flags);
}

// Scookie - Cookie jar management (disabled in FreeMiNT 1.12.4+).
static inline int32_t Scookie(int16_t action, COOKIE *cookie) {
  (void)action;
  (void)cookie;
  return -1;
}

// Shutdown - Kill all processes, sync file-systems then halt or reboot.
static inline int32_t Shutdown(int32_t mode) {
  return (int32_t)trap_1_wl(0x151, (long)mode);
}

// Slbclose - Close a shared library.
static inline int32_t Slbclose(SHARED_LIB *sl) {
  return (int32_t)trap_1_wl(0x17, (long)sl);
}

// Slbopen - Open a shared library.
static inline int32_t Slbopen(int8_t *name, int8_t *path, int32_t min_ver,
                              SHARED_LIB *sl, SLB_EXEC *fn) {
  return (int32_t)trap_1_wlllll(0x16, (long)name, (long)path, (long)min_ver,
                                (long)sl, (long)fn);
}

// Srealloc - Allocate screen memory.
static inline int32_t Srealloc(int32_t len) {
  return (int32_t)trap_1_wl(0x15, (long)len);
}

// Ssystem - Control cookie jar, memory access and various system settings.
static inline int32_t Ssystem(int16_t mode, int32_t arg1, int32_t arg2) {
  return (int32_t)trap_1_wwll(0x154, mode, (long)arg1, (long)arg2);
}

// STEFcntrl - STEmulator control functions.
static inline int32_t STEFcntrl(int16_t func, int32_t special1,
                                int32_t special2) {
  return (int32_t)trap_1_wwll(0x5DC0, func, (long)special1, (long)special2);
}

// Super - Switch supervisor-mode.
static inline int32_t Super(void *stack) {
  return (int32_t)trap_1_wl(0x20, (long)stack);
}

// Suptime - Return the current uptime and load averages.
static inline int32_t Suptime(int32_t *uptime, int32_t *loadaverage) {
  return (int32_t)trap_1_wll(0x13F, (long)uptime, (long)loadaverage);
}

// Sversion - Obtain the number of the current GEMDOS version.
static inline uint16_t Sversion(void) { return (uint16_t)trap_1_w(0x30); }

// Syield - Release CPU for other processes.
static inline void Syield(void) { (void)trap_1_w(0xFF); }

// Sync - Synchronise all mounted file-systems.
static inline void Sync(void) { (void)trap_1_w(0x150); }

// Sysconf - Obtain information about the operating system configuration.
static inline int32_t Sysconf(int16_t n) {
  return (int32_t)trap_1_ww(0x122, n);
}

/* Forward declarations for structures supplied elsewhere. */
typedef struct timeval timeval;
typedef struct timezone timezone;

// Tadjtime - correct the time to synchronize the system clock.
static inline int32_t Tadjtime(const timeval *delta, timeval *olddelta) {
  return (int32_t)trap_1_wll(0x157, (long)delta, (long)olddelta);
}

// Talarm - Reads/sets a process alarm for the current process.
static inline int32_t Talarm(int32_t time) {
  return (int32_t)trap_1_wl(0x120, (long)time);
}

// Tgetdate - Obtain date.
static inline uint16_t Tgetdate(void) { return (uint16_t)trap_1_w(0x2A); }

// Tgettime - Obtain the time.
static inline uint32_t Tgettime(void) { return (uint32_t)trap_1_w(0x2C); }

// Tgettimeofday - Interrogate the state of the internal, high resolution system
// clock.
static inline int32_t Tgettimeofday(timeval *tv, timezone *tzp) {
  return (int32_t)trap_1_wll(0x155, (long)tv, (long)tzp);
}

// Tmalarm - Interrogates the state of the internal, high resolution
// system clock.
static inline int32_t Tmalarm(int32_t time) {
  return (int32_t)trap_1_wl(0x13D, (long)time);
}

// Tsetdate - Set the date.
static inline int16_t Tsetdate(uint16_t date) {
  return (int16_t)trap_1_ww(0x2B, (short)date);
}

// Tsetitimer - Control a periodic timer.
static inline int32_t Tsetitimer(int16_t which, int32_t *interval,
                                 int32_t *value, int32_t *ointerval,
                                 int32_t *ovalue) {
  return (int32_t)trap_1_wwllll(0x149, which, (long)interval, (long)value,
                                (long)ointerval, (long)ovalue);
}

// Tsettime - Set the time.
static inline int16_t Tsettime(uint16_t time) {
  return (int16_t)trap_1_ww(0x2D, (short)time);
}

// Tsettimeofday - Sets the state of the internal, high resolution system clock.
static inline int32_t Tsettimeofday(timeval *tv, timezone *tzp) {
  return (int32_t)trap_1_wll(0x156, (long)tv, (long)tzp);
}

/* Forward declaration for keyboard vector structure. */
typedef struct _KBDVECS _KBDVECS;

// Initmous - Initialise the mouse driver.
static inline void Initmous(int16_t type, void *param, void *handler) {
  (void)trap_14_wwll(0x00, type, (long)param, (long)handler);
}

// Ssbrk - Adjust supervisor memory allocation.
static inline void *Ssbrk(int16_t size) {
  return (void *)trap_14_ww(0x01, size);
}

// Physbase - Return the physical screen base address.
static inline void *Physbase(void) { return (void *)trap_14_w(0x02); }

// Logbase - Return the logical screen base address.
static inline void *Logbase(void) { return (void *)trap_14_w(0x03); }

// Getrez - Report the current video resolution.
static inline int16_t Getrez(void) { return (int16_t)trap_14_w(0x04); }

// Setscreen - Set logical and physical screen addresses and resolution.
static inline void Setscreen(void *lscrn, void *pscrn, int16_t rez) {
  (void)trap_14_wllw(0x05, (long)lscrn, (long)pscrn, rez);
}

// Setpalette - Load the colour palette.
static inline void Setpalette(const void *palptr) {
  (void)trap_14_wl(0x06, (long)palptr);
}

// Setcolor - Set a single colour register.
static inline int16_t Setcolor(int16_t colornum, int16_t mixture) {
  return (int16_t)trap_14_www(0x07, colornum, mixture);
}

// Floprd - Read sectors from a floppy disk.
static inline int16_t Floprd(void *buf, void *x, int16_t dev, int16_t sect,
                             int16_t trk, int16_t side, int16_t n) {
  return (int16_t)trap_14_wllwwwww(0x08, (long)buf, (long)x, dev, sect, trk,
                                   side, n);
}

// Flopwr - Write sectors to a floppy disk.
static inline int16_t Flopwr(const void *buf, const void *x, int16_t dev,
                             int16_t sect, int16_t trk, int16_t side,
                             int16_t n) {
  return (int16_t)trap_14_wllwwwww(0x09, (long)buf, (long)x, dev, sect, trk,
                                   side, n);
}

// Flopfmt - Format tracks on a floppy disk.
static inline int16_t Flopfmt(void *buf, void *x, int16_t dev, int16_t spt,
                              int16_t trk, int16_t sd, int16_t interleave,
                              void *m, int16_t v) {
  return (int16_t)trap_14_wllwwwwwlw(0x0A, (long)buf, (long)x, dev, spt, trk,
                                     sd, interleave, (long)m, v);
}

// Midiws - Send data to the MIDI system.
static inline void Midiws(int16_t count, const void *ptr) {
  (void)trap_14_wwl(0x0C, count, (long)ptr);
}

// Mfpint - Install an MFP interrupt handler.
static inline void Mfpint(int16_t vnum, void (*handler)(void)) {
  (void)trap_14_wwl(0x0D, vnum, (long)handler);
}

// Iorec - Return I/O record information.
static inline void *Iorec(int16_t device) {
  return (void *)trap_14_ww(0x0E, device);
}

// Rsconf - Configure the serial port hardware.
static inline int32_t Rsconf(int16_t baud, int16_t flow, int16_t uc, int16_t rs,
                             int16_t ts, int16_t sc) {
  return (int32_t)trap_14_wwwwwww(0x0F, baud, flow, uc, rs, ts, sc);
}

// Keytbl - Set or query the keyboard translation tables.
static inline void *Keytbl(void *nrml, void *shft, void *caps) {
  return (void *)trap_14_wlll(0x10, (long)nrml, (long)shft, (long)caps);
}

// Random - Return the contents of the 200Hz timer.
static inline int32_t Random(void) { return (int32_t)trap_14_w(0x11); }

// Protobt - Set disk protection info in a boot sector image.
static inline void Protobt(void *buf, int32_t serial, int16_t dsktyp,
                           int16_t exec) {
  (void)trap_14_wllww(0x12, (long)buf, serial, dsktyp, exec);
}

// Flopver - Verify sectors on a floppy disk.
static inline int16_t Flopver(void *buf, void *x, int16_t dev, int16_t sect,
                              int16_t trk, int16_t sd, int16_t n) {
  return (int16_t)trap_14_wllwwwww(0x13, (long)buf, (long)x, dev, sect, trk, sd,
                                   n);
}

// Scrdmp - Dump the screen to printer.
static inline void Scrdmp(void) { (void)trap_14_w(0x14); }

// Cursconf - Configure the mouse cursor.
static inline int16_t Cursconf(int16_t rate, int16_t attr) {
  return (int16_t)trap_14_www(0x15, rate, attr);
}

// Settime - Set the system clock from a DOS time value.
static inline void Settime(int32_t time) { (void)trap_14_wl(0x16, time); }

// Gettime - Read the system clock as a DOS time value.
static inline int32_t Gettime(void) { return (int32_t)trap_14_w(0x17); }

// Bioskeys - Update BIOS keyboard tables from IKBD state.
static inline void Bioskeys(void) { (void)trap_14_w(0x18); }

// Ikbdws - Send a command sequence to the IKBD.
static inline void Ikbdws(int16_t len_minus1, const void *ptr) {
  (void)trap_14_wwl(0x19, len_minus1, (long)ptr);
}

// Jdisint - Disable a specified interrupt vector.
static inline void Jdisint(int16_t vnum) { (void)trap_14_ww(0x1A, vnum); }

// Jenabint - Enable a specified interrupt vector.
static inline void Jenabint(int16_t vnum) { (void)trap_14_ww(0x1B, vnum); }

// Giaccess - Access the General Instrument sound chip.
static inline int16_t Giaccess(int16_t data, int16_t reg) {
  return (int16_t)trap_14_www(0x1C, data, reg);
}

// Offgibit - Clear bits in the general I/O port.
static inline void Offgibit(int16_t ormask) { (void)trap_14_ww(0x1D, ormask); }

// Ongibit - Set bits in the general I/O port.
static inline void Ongibit(int16_t andmask) { (void)trap_14_ww(0x1E, andmask); }

// Xbtimer - Configure an extended BIOS timer.
static inline void Xbtimer(int16_t timer, int16_t ctrl, int16_t data,
                           void (*handler)(void)) {
  (void)trap_14_wwwwl(0x1F, timer, ctrl, data, (long)handler);
}

// Dosound - Execute a sound command sequence.
static inline int32_t Dosound(const void *ptr) {
  return (int32_t)trap_14_wl(0x20, (long)ptr);
}

// Setprt - Configure the printer device.
static inline int16_t Setprt(int16_t config) {
  return (int16_t)trap_14_ww(0x21, config);
}

// Kbdvbase - Return the keyboard vector table base.
static inline _KBDVECS *Kbdvbase(void) { return (_KBDVECS *)trap_14_w(0x22); }

// Kbrate - Set the keyboard repeat rate.
static inline int16_t Kbrate(int16_t delay, int16_t reprate) {
  return (int16_t)trap_14_www(0x23, delay, reprate);
}

// Prtblk - Print a parameter block.
static inline void Prtblk(void *pblkptr) {
  (void)trap_14_wl(0x24, (long)pblkptr);
}

// Vsync - Wait for the vertical blank interval.
static inline void Vsync(void) { (void)trap_14_w(0x25); }

// Supexec - Execute a function in supervisor mode.
static inline int32_t Supexec(int32_t (*funcptr)(void)) {
  return (int32_t)trap_14_wl(0x26, (long)funcptr);
}

// Puntaes - Terminate the AES process.
static inline void Puntaes(void) { (void)trap_14_w(0x27); }

// Floprate - Query or set the floppy data rate.
static inline int16_t Floprate(int16_t drive, int16_t rate) {
  return (int16_t)trap_14_www(0x29, drive, rate);
}

// Blitmode - Query or set the blitter configuration.
static inline int16_t Blitmode(int16_t flag) {
  return (int16_t)trap_14_ww(0x40, flag);
}

// EsetShift - Set extended video shifter mode.
static inline void EsetShift(int16_t mode) { (void)trap_14_ww(80, mode); }

// EgetShift - Get current extended video shifter mode.
static inline int16_t EgetShift(void) { return (int16_t)trap_14_w(81); }

// EsetBank - Select the active video memory bank.
static inline int16_t EsetBank(int16_t bank) {
  return (int16_t)trap_14_ww(82, bank);
}

// EsetColor - Set extended colour register value.
static inline int16_t EsetColor(int16_t num, int16_t val) {
  return (int16_t)trap_14_www(83, num, val);
}

// EsetPalette - Load extended palette entries.
static inline void EsetPalette(int16_t start, int16_t count, const void *ptr) {
  (void)trap_14_wwwl(84, start, count, (long)ptr);
}

// EgetPalette - Read extended palette entries.
static inline void EgetPalette(int16_t start, int16_t count, void *ptr) {
  (void)trap_14_wwwl(85, start, count, (long)ptr);
}

// EsetGray - Enable or disable grayscale mode.
static inline int16_t EsetGray(int16_t mode) {
  return (int16_t)trap_14_ww(86, mode);
}

// EsetSmear - Configure smear reduction mode.
static inline int16_t EsetSmear(int16_t mode) {
  return (int16_t)trap_14_ww(87, mode);
}

// DMAread - Read sectors using the DMA controller.
static inline int32_t DMAread(int32_t sector, int16_t count, void *buffer,
                              int16_t devno) {
  return (int32_t)trap_14_wlwlw(0x2A, sector, count, (long)buffer, devno);
}

// DMAwrite - Write sectors using the DMA controller.
static inline int32_t DMAwrite(int32_t sector, int16_t count,
                               const void *buffer, int16_t devno) {
  return (int32_t)trap_14_wlwlw(0x2B, sector, count, (long)buffer, devno);
}

// Bconmap - Remap console device handles.
static inline int32_t Bconmap(int16_t dev) {
  return (int32_t)trap_14_ww(0x2C, dev);
}

// NVMaccess - Access non-volatile memory storage.
static inline int16_t NVMaccess(int16_t op, int16_t start, int16_t count,
                                void *buf) {
  return (int16_t)trap_14_wwwwl(0x2E, op, start, count, (long)buf);
}

// Waketime - Schedule a wake-up with DOS date/time values.
static inline void Waketime(uint16_t w_date, uint16_t w_time) {
  (void)trap_14_www(0x2F, (short)w_date, (short)w_time);
}

#endif
