#include <math.h>

double ldexp(double x, int exp) { return __builtin_ldexp(x, exp); }
float ldexpf(float x, int exp) { return __builtin_ldexpf(x, exp); }
long double ldexpl(long double x, int exp) { return __builtin_ldexpl(x, exp); }
