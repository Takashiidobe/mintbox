#include <stdint.h>
#include <stdlib.h>

static uint32_t rand_state = 1;

int rand(void) {
  rand_state = rand_state * 1103515245u + 12345u;
  return (int)(rand_state & RAND_MAX);
}

void srand(unsigned int seed) {
  rand_state = seed ? seed : 1u;
}
