int ispunct(int c) {
  unsigned cc = (unsigned)c;
  if (cc < '!' || cc > '~') {
    return 0;
  }
  if (cc - '0' <= 9) {
    return 0;
  }
  return ((cc | 32) - 'a') >= 26;
}
