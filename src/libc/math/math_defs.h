#ifndef LIBC_MATH_MATH_DEFS_H
#define LIBC_MATH_MATH_DEFS_H

#include <math.h>

#define DEF_UNARY(name)                                                        \
  double name(double x) { return __builtin_##name(x); }                        \
  float name##f(float x) { return __builtin_##name##f(x); }                    \
  long double name##l(long double x) { return __builtin_##name##l(x); }

#define DEF_BINARY(name)                                                       \
  double name(double x, double y) { return __builtin_##name(x, y); }           \
  float name##f(float x, float y) { return __builtin_##name##f(x, y); }        \
  long double name##l(long double x, long double y) {                          \
    return __builtin_##name##l(x, y);                                          \
  }

#endif /* LIBC_MATH_MATH_DEFS_H */
