#ifndef F_ENV_C
#define F_ENV_C

#include <fenv.h>

int feclearexcept(int _) { return -1; }
int fegetexceptflag(fexcept_t *_, int _flag) { return -1; }
int feraiseexcept(int _) { return -1; }
int fesetexceptflag(const fexcept_t *_, int _flag) { return -1; }
int fetestexcept(int _) { return -1; }

int fegetround(void) { return -1; }
int fesetround(int _) { return -1; }

int fegetenv(fenv_t *_) { return -1; }
int feholdexcept(fenv_t *_) { return -1; }
int fesetenv(const fenv_t *_) { return -1; }
int feupdateenv(const fenv_t *_) { return -1; }

#endif
