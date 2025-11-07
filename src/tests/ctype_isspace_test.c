#include <assert.h>
#include <ctype.h>

static int is_space_char(int c) {
  switch (c) {
  case ' ':
  case '\f':
  case '\n':
  case '\r':
  case '\t':
  case '\v':
    return 1;
  default:
    return 0;
  }
}

int main(void) {
  for (int c = 0; c < 128; ++c) {
    int expected = is_space_char(c);
    int actual = isspace(c) != 0;
    assert(actual == expected);
  }
  return 0;
}
