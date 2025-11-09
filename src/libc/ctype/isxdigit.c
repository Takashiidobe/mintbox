int isxdigit(int c) {
  unsigned cc = (unsigned)c;
  if (cc - '0' <= 9) {
    return 1;
  }
  cc |= 32;
  return cc - 'a' < 6;
}
