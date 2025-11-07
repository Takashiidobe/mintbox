#include <stdio.h>

// This fgets handles "\r\n"
char *fgets(char *s, int n, FILE *fp) {
  if (n <= 0)
    return NULL;
  int i = 0;

  while (i < n - 1) {
    int ch = fgetc(fp);
    if (ch == EOF)
      break;
    s[i++] = (char)ch;
    if (ch == '\n')
      break;
  }

  if (i == 0)
    return NULL;
  s[i] = '\0';
  return s;
}
