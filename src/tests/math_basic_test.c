#include <assert.h>
#include <math.h>

static int almost_equal(double a, double b) {
  double diff = a - b;
  if (diff < 0) {
    diff = -diff;
  }
  return diff < 1e-9;
}

int main(void) {
  assert(almost_equal(sin(0.0), 0.0));
  assert(almost_equal(cos(0.0), 1.0));
  assert(almost_equal(tan(M_PI_4), 1.0));
  assert(almost_equal(sqrt(4.0), 2.0));
  assert(almost_equal(pow(2.0, 3.0), 8.0));
  assert(almost_equal(exp(1.0), M_E));
  assert(almost_equal(log(M_E), 1.0));

  int exponent = 0;
  double mantissa = frexp(8.0, &exponent);
  assert(almost_equal(mantissa, 0.5));
  assert(exponent == 4);
  assert(almost_equal(ldexp(mantissa, exponent), 8.0));

  double int_part = 0.0;
  double frac_part = modf(3.75, &int_part);
  assert(almost_equal(int_part, 3.0));
  assert(almost_equal(frac_part, 0.75));

  assert(almost_equal(fmod(7.0, 3.0), 1.0));

  return 0;
}
