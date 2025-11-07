#ifndef LIBC_CTYPE_H
#define LIBC_CTYPE_H

#define _C 0x01 // Control
#define _U 0x04 // Upper
#define _N 0x04 // Digit
#define _L 0x08 // Lower
#define _S 0x10 // Space
#define _P 0x20 // Punct
#define _X 0x40 // Hexdigit
#define _B 0x80 // Blank

extern const unsigned char _ctype[256];

#define isalpha(c) ((_ctype + 1)[(unsigned char)(c)] & (_U | _L))
#define isupper(c) ((_ctype + 1)[(unsigned char)(c)] & _U)
#define islower(c) ((_ctype + 1)[(unsigned char)(c)] & _L)
#define isdigit(c) ((_ctype + 1)[(unsigned char)(c)] & _N)
#define isxdigit(c) ((_ctype + 1)[(unsigned char)(c)] & _X)
#define isspace(c) ((_ctype + 1)[(unsigned char)(c)] & _S)
#define ispunct(c) ((_ctype + 1)[(unsigned char)(c)] & _P)
#define isalnum(c) ((_ctype + 1)[(unsigned char)(c)] & (_U | _L | _N))
#define isprint(c) ((_ctype + 1)[(unsigned char)(c)] & (_P | _U | _L | _N | _B))
#define isgraph(c) ((_ctype + 1)[(unsigned char)(c)] & (_P | _U | _L | _N))
#define iscntrl(c) ((_ctype + 1)[(unsigned char)(c)] & _C)
#define toupper(c) (islower(c) ? (c) - 'a' + 'A' : (c))
#define tolower(c) (isupper(c) ? (c) - 'A' + 'a' : (c))

#endif /* LIBC_CTYPE_H */
