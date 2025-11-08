#ifndef FENV_H
#define FENV_H

typedef unsigned short fexcept_t;

typedef struct {
  unsigned short int __control_word;
  unsigned short int __glibc_reserved1;
  unsigned short int __status_word;
  unsigned short int __glibc_reserved2;
  unsigned short int __tags;
  unsigned short int __glibc_reserved3;
  unsigned int __eip;
  unsigned short int __cs_selector;
  unsigned int __opcode : 11;
  unsigned int __glibc_reserved4 : 5;
  unsigned int __data_offset;
  unsigned short int __data_selector;
  unsigned short int __glibc_reserved5;
} fenv_t;

int feclearexcept(int);
int fegetexceptflag(fexcept_t *, int);
int feraiseexcept(int);
int fesetexceptflag(const fexcept_t *, int);
int fetestexcept(int);

int fegetround(void);
int fesetround(int);

int fegetenv(fenv_t *);
int feholdexcept(fenv_t *);
int fesetenv(const fenv_t *);
int feupdateenv(const fenv_t *);

#endif
