#include <assert.h>
#include <ctype.h>

int main(void) {
  for (int c = 0; c < 128; ++c) {
    int expected = (c >= '0' && c <= '9');
    int actual = isdigit(c) != 0;
    assert(actual == expected);
  }
  return 0;
}
