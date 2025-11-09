#include <math.h>

double frexp(double x, int *exp) { return __builtin_frexp(x, exp); }
float frexpf(float x, int *exp) { return __builtin_frexpf(x, exp); }
long double frexpl(long double x, int *exp) {
  return __builtin_frexpl(x, exp);
}
