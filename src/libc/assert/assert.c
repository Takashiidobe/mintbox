#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__)) void
__assert_fail(const char *expr, const char *file, int line, const char *func) {
  if (!expr)
    expr = "0";
  if (!file)
    file = "unknown";
  if (!func)
    func = "unknown";

  fprintf(stderr, "Assertion failed: (%s), function %s, file %s, line %d.\n",
          expr, func, file, line);
  exit(EXIT_FAILURE);
}
