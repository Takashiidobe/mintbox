#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // int *x = malloc(sizeof(int) * 10);
  // for (int i = 0; i < 10; i++) {
  //   x[i] = i;
  // }
  // char buf[12];
  // for (int i = 0; i < 10; i++) {
  //   puts(itoa(buf, x[i]));
  // }

  char buf[12];
  for (int i = 0; i < 10; i++) {
    puts(itoa(buf, i));
  }

  return 0;
}
