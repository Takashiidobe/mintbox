#include <assert.h>
#include <ctype.h>

int main(void) {
  for (int c = 0; c < 128; ++c) {
    int expected = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
    int actual = isalpha(c) != 0;
    assert(actual == expected);
  }
  return 0;
}
