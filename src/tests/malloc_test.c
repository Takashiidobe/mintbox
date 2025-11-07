#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int *x = malloc(sizeof(int) * 10);
  for (int i = 0; i < 10; i++) {
    x[i] = i;
  }
  for (int i = 0; i < 10; i++) {
    assert(x[i] == i);
    printf("%d\r\n", x[i]);
  }

  return 0;
}
