int puts(const char *s) {
  if (*s)
    putch(*s);
  while (*s++ != '\0') {
    putch(*s);
  }
  putch('\n');
}
