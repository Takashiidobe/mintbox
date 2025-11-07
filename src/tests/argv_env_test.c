#include <stdio.h>
#include <stdlib.h>

extern char **environ;

static void dump_env(const char *label, char **env, int limit) {
  puts(label);
  if (!env)
    return;

  for (int i = 0; env[i] && i < limit; ++i) {
    printf("[%d] %s\n", i, env[i]);
  }
}

int main(int argc, char **argv, char **envp) {
  printf("argc = %d\n", argc);
  for (int i = 0; i < argc; ++i) {
    printf("argv[%d] = \"%s\"\n", i, argv[i]);
  }

  dump_env("-- initial environ --", envp, 5);

  char *demo_val = getenv("ARGV_ENV_TEST");
  if (demo_val)
    printf("Found ARGV_ENV_TEST=%s\n", demo_val);
  else
    puts("ARGV_ENV_TEST not set");

  static char var1[] = "CUSTOM_ONE=foo";
  static char var2[] = "CUSTOM_TWO=bar";
  static char var3[] = "CUSTOM_ONE=baz";

  if (putenv(var1) != 0 || putenv(var2) != 0 || putenv(var3) != 0) {
    puts("putenv failed");
    return 1;
  }

  dump_env("-- environ after putenv --", environ, 6);
  char *one = getenv("CUSTOM_ONE");
  char *two = getenv("CUSTOM_TWO");
  printf("CUSTOM_ONE via getenv: %s\n", one ? one : "(null)");
  printf("CUSTOM_TWO via getenv: %s\n", two ? two : "(null)");

  if (setenv("SETENV_ONE", "alpha", 0) != 0 ||
      setenv("SETENV_ONE", "beta", 0) != 0) {
    puts("setenv (no overwrite) failed");
    return 1;
  }
  printf("SETENV_ONE after no-overwrite setenv: %s\n",
         getenv("SETENV_ONE"));

  if (setenv("SETENV_ONE", "gamma", 1) != 0) {
    puts("setenv overwrite failed");
    return 1;
  }
  printf("SETENV_ONE after overwrite setenv: %s\n", getenv("SETENV_ONE"));

  if (unsetenv("CUSTOM_TWO") != 0) {
    puts("unsetenv failed");
    return 1;
  }
  dump_env("-- environ after unsetenv CUSTOM_TWO --", environ, 6);

  if (clearenv() != 0) {
    puts("clearenv failed");
    return 1;
  }
  dump_env("-- environ after clearenv --", environ, 6);

  if (setenv("POST_CLEAR", "1", 1) != 0) {
    puts("setenv after clearenv failed");
    return 1;
  }
  dump_env("-- environ after repopulating --", environ, 6);

  return 0;
}
