#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

static char **managed_env = NULL;

static size_t env_count(void) {
  size_t count = 0;
  if (!environ) {
    return 0;
  }
  while (environ[count]) {
    ++count;
  }
  return count;
}

static int ensure_env_heap(void) {
  if (!environ) {
    char **block = malloc(sizeof(char *));
    if (!block) {
      errno = ENOMEM;
      return -1;
    }
    block[0] = NULL;
    environ = block;
    managed_env = block;
    return 0;
  }

  if (environ == managed_env) {
    return 0;
  }

  size_t count = env_count();
  char **copy = malloc((count + 1) * sizeof(char *));
  if (!copy) {
    errno = ENOMEM;
    return -1;
  }
  for (size_t i = 0; i <= count; ++i) {
    copy[i] = environ[i];
  }
  environ = copy;
  managed_env = copy;
  return 0;
}

static int match_name(const char *entry, const char *name, size_t name_len) {
  if (!entry) {
    return 0;
  }
  return strncmp(entry, name, name_len) == 0 && entry[name_len] == '=';
}

char *getenv(const char *name) {
  if (!name || !*name || strchr(name, '=')) {
    return NULL;
  }

  if (!environ) {
    return NULL;
  }

  size_t name_len = strlen(name);
  for (char **entry = environ; *entry; ++entry) {
    if (match_name(*entry, name, name_len)) {
      return *entry + name_len + 1;
    }
  }

  return NULL;
}

int putenv(char *string) {
  if (!string) {
    errno = EINVAL;
    return -1;
  }

  char *eq = strchr(string, '=');
  if (!eq || eq == string) {
    errno = EINVAL;
    return -1;
  }

  size_t name_len = (size_t)(eq - string);

  if (ensure_env_heap() < 0) {
    return -1;
  }

  for (char **entry = environ; *entry; ++entry) {
    if (match_name(*entry, string, name_len)) {
      *entry = string;
      return 0;
    }
  }

  size_t count = env_count();
  char **new_env = realloc(environ, (count + 2) * sizeof(char *));
  if (!new_env) {
    errno = ENOMEM;
    return -1;
  }

  environ = new_env;
  managed_env = new_env;
  environ[count] = string;
  environ[count + 1] = NULL;
  return 0;
}

int clearenv(void) {
  if (managed_env) {
    environ = managed_env;
    environ[0] = NULL;
    return 0;
  }

  if (!environ) {
    return ensure_env_heap();
  }

  char **block = malloc(sizeof(char *));
  if (!block) {
    errno = ENOMEM;
    return -1;
  }
  block[0] = NULL;
  environ = block;
  managed_env = block;
  return 0;
}

int unsetenv(const char *name) {
  if (!name || !*name || strchr(name, '=')) {
    errno = EINVAL;
    return -1;
  }

  if (!environ) {
    return 0;
  }

  if (ensure_env_heap() < 0) {
    return -1;
  }

  size_t name_len = strlen(name);
  char **src = environ;
  char **dst = environ;
  while (*src) {
    if (!match_name(*src, name, name_len)) {
      *dst++ = *src;
    }
    ++src;
  }
  *dst = NULL;
  return 0;
}

int setenv(const char *name, const char *value, int overwrite) {
  if (!name || !*name || strchr(name, '=')) {
    errno = EINVAL;
    return -1;
  }

  if (!value) {
    value = "";
  }

  if (!overwrite && getenv(name)) {
    return 0;
  }

  if (overwrite) {
    if (unsetenv(name) < 0) {
      return -1;
    }
  }

  size_t name_len = strlen(name);
  size_t value_len = strlen(value);
  size_t suffix = value_len + 2; // '=' + value + '\0'
  if (suffix < value_len) {
    errno = ENOMEM;
    return -1;
  }

  if (name_len > SIZE_MAX - suffix) {
    errno = ENOMEM;
    return -1;
  }

  size_t total = name_len + suffix;
  char *entry = malloc(total);
  if (!entry) {
    errno = ENOMEM;
    return -1;
  }

  memcpy(entry, name, name_len);
  entry[name_len] = '=';
  memcpy(entry + name_len + 1, value, value_len);
  entry[total - 1] = '\0';

  if (putenv(entry) != 0) {
    free(entry);
    return -1;
  }

  return 0;
}
