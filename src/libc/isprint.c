#include <ctype.h>

#undef isprint

int isprint(int c) { return c >= 0x20 && c <= 0x7E; }
