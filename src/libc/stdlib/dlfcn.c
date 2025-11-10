#include <dlfcn.h>
#include <stddef.h>

void *dlopen(const char *path, int mode) {
  (void)path;
  (void)mode;
  return NULL;
}

int dlclose(void *handle) {
  (void)handle;
  return -1;
}

void *dlsym(void *handle, const char *symbol) {
  (void)handle;
  (void)symbol;
  return NULL;
}

char *dlerror(void) { return "dynamic loading not supported"; }
