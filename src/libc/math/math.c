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

DEF_UNARY(sin)
DEF_UNARY(cos)
DEF_UNARY(tan)
DEF_UNARY(asin)
DEF_UNARY(acos)
DEF_UNARY(atan)
DEF_BINARY(atan2)
DEF_UNARY(sinh)
DEF_UNARY(cosh)
DEF_UNARY(tanh)
DEF_UNARY(exp)
DEF_UNARY(exp2)
DEF_UNARY(expm1)
DEF_UNARY(log)
DEF_UNARY(log10)
DEF_UNARY(log2)
DEF_UNARY(log1p)
DEF_BINARY(pow)
DEF_UNARY(sqrt)
DEF_UNARY(cbrt)
DEF_BINARY(hypot)
DEF_UNARY(fabs)
DEF_BINARY(copysign)
DEF_UNARY(floor)
DEF_UNARY(ceil)
DEF_UNARY(trunc)
DEF_UNARY(round)
DEF_BINARY(fmod)

double frexp(double x, int *exp) { return __builtin_frexp(x, exp); }
float frexpf(float x, int *exp) { return __builtin_frexpf(x, exp); }
long double frexpl(long double x, int *exp) {
  return __builtin_frexpl(x, exp);
}

double ldexp(double x, int exp) { return __builtin_ldexp(x, exp); }
float ldexpf(float x, int exp) { return __builtin_ldexpf(x, exp); }
long double ldexpl(long double x, int exp) { return __builtin_ldexpl(x, exp); }

double modf(double x, double *iptr) { return __builtin_modf(x, iptr); }
float modff(float x, float *iptr) { return __builtin_modff(x, iptr); }
long double modfl(long double x, long double *iptr) {
  return __builtin_modfl(x, iptr);
}
