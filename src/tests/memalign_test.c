#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  const size_t alignment = 64;
  const size_t length = 16;

  uint32_t *buffer = memalign(alignment, length * sizeof(*buffer));
  if (buffer == NULL) {
    printf("memalign failed\r\n");
    return 1;
  }

  const uintptr_t addr = (uintptr_t)buffer;
  printf("buffer=%p alignment=%zu\r\n", (void *)buffer, alignment);
  if (addr % alignment != 0) {
    printf("alignment check failed\r\n");
    free(buffer);
    return 2;
  }

  for (size_t i = 0; i < length; ++i) {
    buffer[i] = 0x12340000u + (uint32_t)i;
  }

  for (size_t i = 0; i < length; ++i) {
    printf("[%02zu]=0x%08lx\r\n", i, (unsigned long)buffer[i]);
  }

  free(buffer);
  return 0;
}
