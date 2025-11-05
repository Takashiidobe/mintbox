#ifndef LIBC_ASSERT_H
#define LIBC_ASSERT_H

void __assert_fail(const char *expr, const char *file, int line,
                   const char *func) __attribute__((__noreturn__));

#ifdef NDEBUG
#define assert(expr) ((void)0)
#else
#define assert(expr)                                                           \
  ((expr) ? (void)0 : __assert_fail(#expr, __FILE__, __LINE__, __func__))
#endif

#endif /* LIBC_ASSERT_H */
