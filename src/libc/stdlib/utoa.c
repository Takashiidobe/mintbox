char *utoa(char *dst, unsigned long value) {
  char *p = dst;

  do {
    *p++ = '0' + (value % 10);
    value /= 10;
  } while (value);

  *p = '\0';

  for (char *lo = dst, *hi = p - 1; lo < hi; ++lo, --hi) {
    char tmp = *lo;
    *lo = *hi;
    *hi = tmp;
  }
  return p;
}
