#include <assert.h>
#include <ctype.h>

int main(void) {
  for (int c = 0; c < 128; ++c) {
    int expected = (c >= 0x20 && c <= 0x7e);
    int actual = isprint(c) != 0;
    assert(actual == expected);
  }
  return 0;
}
