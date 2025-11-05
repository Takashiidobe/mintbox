char *itoa(char *dst, long value) {
  char *p = dst;
  int negative = value < 0;

  do {
    int digit = value % 10;
    if (digit < 0)
      digit = -digit;
    *p++ = '0' + digit;
    value /= 10;
  } while (value);

  if (negative)
    *p++ = '-';

  *p = '\0';

  for (char *lo = dst, *hi = p - 1; lo < hi; ++lo, --hi) {
    char tmp = *lo;
    *lo = *hi;
    *hi = tmp;
  }
  return p;
}
