#include <assert.h>
#include <string.h>

int main(void) {
  char text[] = "hello world";
  assert(strrchr(text, 'o') == text + 7);
  assert(strrchr(text, '\0') == text + strlen(text));
  assert(strrchr(text, 'z') == NULL);

  assert(strspn("abcde3123", "abcde") == 5);
  assert(strcspn("abcde3123", "1234567890") == 5);
  char text2[] = "mintbox";
  assert(strpbrk(text2, "xyz") == NULL);
  assert(strpbrk(text2, "ob") == text2 + 4);

  char buffer[] = "one,two,,three";
  char *tok = strtok(buffer, ",");
  assert(strcmp(tok, "one") == 0);
  tok = strtok(NULL, ",");
  assert(strcmp(tok, "two") == 0);
  tok = strtok(NULL, ",");
  assert(strcmp(tok, "") == 0);
  tok = strtok(NULL, ",");
  assert(strcmp(tok, "three") == 0);
  assert(strtok(NULL, ",") == NULL);

  char buffer2[] = "a::b:c";
  char *save = NULL;
  tok = strtok_r(buffer2, ":", &save);
  assert(strcmp(tok, "a") == 0);
  tok = strtok_r(NULL, ":", &save);
  assert(strcmp(tok, "") == 0);
  tok = strtok_r(NULL, ":", &save);
  assert(strcmp(tok, "b") == 0);
  tok = strtok_r(NULL, ":", &save);
  assert(strcmp(tok, "c") == 0);
  assert(strtok_r(NULL, ":", &save) == NULL);

  assert(strcasecmp("Hello", "heLLo") == 0);
  assert(strcasecmp("abc", "abd") < 0);
  assert(strncasecmp("abc", "ABD", 2) == 0);
  assert(strncasecmp("abc", "ABD", 3) < 0);

  char mem_buf[10] = {0};
  const char *source = "abcdef";
  void *ret = memccpy(mem_buf, source, 'd', 6);
  assert(ret == mem_buf + 4);
  assert(mem_buf[3] == 'd');

  char mem_buf2[10] = {0};
  ret = mempcpy(mem_buf2, source, 3);
  assert(ret == mem_buf2 + 3);
  assert(mem_buf2[0] == 'a' && mem_buf2[2] == 'c');

  const char *hay = "abcdeabc";
  const char *needle = "dea";
  assert(memmem(hay, strlen(hay), needle, 3) == hay + 3);
  assert(memmem(hay, strlen(hay), "xyz", 3) == NULL);
  assert(memmem(hay, strlen(hay), "", 0) == hay);

  return 0;
}
