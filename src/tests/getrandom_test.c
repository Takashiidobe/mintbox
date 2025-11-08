#include <stdint.h>
#include <stdio.h>
#include <sys/random.h>

int main(void) {
  for (int i = 0; i < 10; ++i) {
    uint32_t value = 0;
    if (getrandom(&value, sizeof(value), 0) < 0) {
      perror("getrandom");
      return 1;
    }
    printf("rand[%d] = 0x%08x\n", i, value);
  }
  return 0;
}
