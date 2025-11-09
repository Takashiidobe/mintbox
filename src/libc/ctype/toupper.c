int toupper(int c) {
  if ((unsigned)c - 'a' < 26) {
    return c - ('a' - 'A');
  }
  return c;
}
