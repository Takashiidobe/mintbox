#include <math.h>

double modf(double x, double *iptr) { return __builtin_modf(x, iptr); }
float modff(float x, float *iptr) { return __builtin_modff(x, iptr); }
long double modfl(long double x, long double *iptr) {
  return __builtin_modfl(x, iptr);
}
