#ifndef LIBC_CTYPE_H
#define LIBC_CTYPE_H

int isspace(int c);
int isdigit(int c);
int isprint(int c);
int isalnum(int c);
int isalpha(int c);
int islower(int c);
int isupper(int c);
int isxdigit(int c);
int isgraph(int c);
int iscntrl(int c);
int ispunct(int c);
int isascii(int c);
int toascii(int c);
int tolower(int c);
int toupper(int c);

#endif /* LIBC_CTYPE_H */
