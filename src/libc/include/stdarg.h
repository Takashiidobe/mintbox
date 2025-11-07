#ifndef _STDARG_H
#define _STDARG_H

/* GCC/Clang expose a target-correct va_list and helpers as built-ins.
   Using them avoids ABI pitfalls (alignment, promotion rules, etc.). */
#ifndef __GNUC__
#error "This stdarg.h expects a GCC/Clang-compatible compiler."
#endif

typedef __builtin_va_list va_list;

#define va_start(ap, last_param) __builtin_va_start((ap), (last_param))
#define va_arg(ap, type) __builtin_va_arg((ap), type)
#define va_end(ap) __builtin_va_end(ap)

/* C99: va_copy; older GCCs may not have __builtin_va_copy — fall back to assign
 */
#if defined(__builtin_va_copy) || (__GNUC__ >= 3)
#define va_copy(dst, src) __builtin_va_copy((dst), (src))
#else
#define va_copy(dst, src) ((dst) = (src))
#endif

#endif
