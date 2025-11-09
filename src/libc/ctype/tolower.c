int tolower(int c) {
  if ((unsigned)c - 'A' < 26) {
    return c + ('a' - 'A');
  }
  return c;
}
