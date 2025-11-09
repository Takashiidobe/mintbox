#include <assert.h>
#include <ctype.h>

int main(void) {
  assert(islower('a'));
  assert(!islower('A'));
  assert(isupper('Z'));
  assert(!isupper('z'));

  assert(isxdigit('0'));
  assert(isxdigit('9'));
  assert(isxdigit('a') && isxdigit('F'));
  assert(!isxdigit('g'));

  assert(isgraph('!'));
  assert(!isgraph(' '));
  assert(iscntrl('\n'));
  assert(!iscntrl('A'));

  assert(ispunct('!'));
  assert(!ispunct('A'));
  assert(!ispunct(' '));

  assert(isascii(0x7f));
  assert(!isascii(0x80));
  assert(toascii(0x180) == 0x80);

  assert(tolower('A') == 'a');
  assert(tolower('a') == 'a');
  assert(toupper('a') == 'A');
  assert(toupper('A') == 'A');

  return 0;
}
