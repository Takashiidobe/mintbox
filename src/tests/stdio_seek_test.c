#include <stdio.h>
#include <unistd.h>

int main(void) {
  clearerr(stdin);
  (void)feof(stdin);
  (void)ftell(stdin);
  fseek(stdin, 0, SEEK_CUR);
  rewind(stdin);
  return 0;
}
