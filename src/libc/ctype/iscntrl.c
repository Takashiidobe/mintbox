int iscntrl(int c) {
  unsigned cc = (unsigned)c;
  return cc < 0x20 || cc == 0x7f;
}
