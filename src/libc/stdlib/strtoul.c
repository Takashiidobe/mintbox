#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

static int digit_value(int c) {
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c >= 'a' && c <= 'z')
    return c - 'a' + 10;
  if (c >= 'A' && c <= 'Z')
    return c - 'A' + 10;
  return -1;
}

unsigned long strtoul(const char *nptr, char **endptr, int base) {
  const char *s = nptr;
  unsigned long acc = 0;
  int neg = 0;
  int any = 0;
  int overflow = 0;

  if (base && (base < 2 || base > 36)) {
    errno = EINVAL;
    if (endptr)
      *endptr = (char *)nptr;
    return 0;
  }

  while (isspace((unsigned char)*s))
    s++;

  if (*s == '+' || *s == '-') {
    neg = (*s == '-');
    s++;
  }

  if ((base == 0 || base == 16) && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
    base = 16;
    s += 2;
  } else if (base == 0) {
    base = (s[0] == '0') ? 8 : 10;
  }

  if (base == 0)
    base = 10;

  unsigned long cutoff = ULONG_MAX / (unsigned long)base;
  unsigned long cutlim = ULONG_MAX % (unsigned long)base;

  while (*s) {
    int digit = digit_value(*s);
    if (digit < 0 || digit >= base)
      break;
    if (!overflow) {
      if (acc > cutoff || (acc == cutoff && (unsigned long)digit > cutlim))
        overflow = 1;
      else
        acc = acc * (unsigned long)base + (unsigned long)digit;
    }
    any = 1;
    s++;
  }

  if (!any) {
    if (endptr)
      *endptr = (char *)nptr;
    return 0;
  }

  if (endptr)
    *endptr = (char *)s;

  if (overflow) {
    errno = ERANGE;
    return ULONG_MAX;
  }

  if (neg)
    acc = 0UL - acc;

  return acc;
}
