#include <assert.h>
#include <ctype.h>

static int is_alpha(int c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int main(void) {
  for (int c = 0; c < 128; ++c) {
    int expected = is_alpha(c) || (c >= '0' && c <= '9');
    int actual = isalnum(c) != 0;
    assert(actual == expected);
  }
  return 0;
}
