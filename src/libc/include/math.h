#ifndef LIBC_MATH_H
#define LIBC_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD 0
#endif

#if FLT_EVAL_METHOD == 0
typedef float float_t;
typedef double double_t;
#elif FLT_EVAL_METHOD == 1
typedef double float_t;
typedef double double_t;
#elif FLT_EVAL_METHOD == 2
typedef long double float_t;
typedef long double double_t;
#else
typedef double float_t;
typedef double double_t;
#endif

#define FP_NAN 0
#define FP_INFINITE 1
#define FP_NORMAL 2
#define FP_SUBNORMAL 3
#define FP_ZERO 4

#define HUGE_VAL (__builtin_huge_val())
#define HUGE_VALF (__builtin_huge_valf())
#define HUGE_VALL (__builtin_huge_vall())
#define INFINITY (__builtin_inff())
#define NAN (__builtin_nanf(""))

#define fpclassify(x)                                                          \
  __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO,   \
                       (x))
#define isfinite(x) __builtin_isfinite(x)
#define isinf(x) __builtin_isinf_sign(x)
#define isnan(x) __builtin_isnan(x)
#define isnormal(x) __builtin_isnormal(x)
#define signbit(x) __builtin_signbit(x)

#define M_E 2.71828182845904523536
#define M_LOG2E 1.44269504088896340736
#define M_LOG10E 0.43429448190325182765
#define M_LN2 0.69314718055994530942
#define M_LN10 2.30258509299404568402
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define M_PI_4 0.78539816339744830962
#define M_1_PI 0.31830988618379067154
#define M_2_PI 0.63661977236758134308
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2 1.41421356237309504880
#define M_SQRT1_2 0.70710678118654752440

double sin(double);
float sinf(float);
long double sinl(long double);

double cos(double);
float cosf(float);
long double cosl(long double);

double tan(double);
float tanf(float);
long double tanl(long double);

double asin(double);
float asinf(float);
long double asinl(long double);

double acos(double);
float acosf(float);
long double acosl(long double);

double atan(double);
float atanf(float);
long double atanl(long double);

double atan2(double, double);
float atan2f(float, float);
long double atan2l(long double, long double);

double sinh(double);
float sinhf(float);
long double sinhl(long double);

double cosh(double);
float coshf(float);
long double coshl(long double);

double tanh(double);
float tanhf(float);
long double tanhl(long double);

double exp(double);
float expf(float);
long double expl(long double);

double exp2(double);
float exp2f(float);
long double exp2l(long double);

double expm1(double);
float expm1f(float);
long double expm1l(long double);

double log(double);
float logf(float);
long double logl(long double);

double log10(double);
float log10f(float);
long double log10l(long double);

double log2(double);
float log2f(float);
long double log2l(long double);

double log1p(double);
float log1pf(float);
long double log1pl(long double);

double pow(double, double);
float powf(float, float);
long double powl(long double, long double);

double sqrt(double);
float sqrtf(float);
long double sqrtl(long double);

double cbrt(double);
float cbrtf(float);
long double cbrtl(long double);

double hypot(double, double);
float hypotf(float, float);
long double hypotl(long double, long double);

double fabs(double);
float fabsf(float);
long double fabsl(long double);

double copysign(double, double);
float copysignf(float, float);
long double copysignl(long double, long double);

double floor(double);
float floorf(float);
long double floorl(long double);

double ceil(double);
float ceilf(float);
long double ceill(long double);

double trunc(double);
float truncf(float);
long double truncl(long double);

double round(double);
float roundf(float);
long double roundl(long double);

double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);

double frexp(double, int *);
float frexpf(float, int *);
long double frexpl(long double, int *);

double ldexp(double, int);
float ldexpf(float, int);
long double ldexpl(long double, int);

double modf(double, double *);
float modff(float, float *);
long double modfl(long double, long double *);

#ifdef __cplusplus
}
#endif

#endif /* LIBC_MATH_H */
