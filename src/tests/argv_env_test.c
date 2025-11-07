#include <stdio.h>

extern char **environ;

static const char *find_env(const char *name) {
  if (!environ || !name)
    return NULL;

  for (char **entry = environ; *entry; ++entry) {
    const char *pair = *entry;
    const char *key = name;
    while (*pair && *key && *pair == *key) {
      ++pair;
      ++key;
    }
    if (*key == '\0' && *pair == '=')
      return pair + 1;
  }
  return NULL;
}

int main(int argc, char **argv, char **envp) {
  printf("argc = %d\n", argc);
  for (int i = 0; i < argc; ++i) {
    printf("argv[%d] = \"%s\"\n", i, argv[i]);
  }

  puts("-- initial environ --");
  if (envp) {
    for (int i = 0; envp[i] && i < 5; ++i) {
      printf("envp[%d] = \"%s\"\n", i, envp[i]);
    }
  }

  const char *demo_val = find_env("ARGV_ENV_TEST");
  if (demo_val)
    printf("Found ARGV_ENV_TEST=%s\n", demo_val);
  else
    puts("ARGV_ENV_TEST not set");

  static char var1[] = "CUSTOM_ONE=foo";
  static char var2[] = "CUSTOM_TWO=bar";
  static char *custom_env[] = {var1, var2, NULL};

  environ = custom_env;
  puts("-- overridden environ --");
  for (int i = 0; environ[i]; ++i) {
    printf("environ[%d] = \"%s\"\n", i, environ[i]);
  }

  return 0;
}
