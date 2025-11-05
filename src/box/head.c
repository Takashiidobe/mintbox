/* head.c: minimal head(1) for Atari MiNT using stdio.
 *
 * Usage:
 *   head [-n N] FILE
 *   head [-n N] -        # read from stdin
 *
 * Default N = 10.
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SZ 512

static int head_stream(FILE *in, size_t n) {
  unsigned char buf[BUF_SZ];
  size_t lines = 0;

  for (;;) {
    size_t r = fread(buf, 1, BUF_SZ, in);
    if (r == 0) {
      if (ferror(in))
        return -1;
      break; // EOF
    }

    size_t upto = r;
    for (size_t i = 0; i < r; i++) {
      if (buf[i] == '\n') {
        lines++;
        if (lines == n) {
          upto = i + 1;
          if (fwrite(buf, 1, upto, stdout) != upto)
            return -1;
          return 0;
        }
      } else if (buf[i] == '\r') {
        lines++;
        if (i + 1 < r && buf[i + 1] == '\n') {
        }
        if (lines == n) {
          upto = (i + 1 < r && buf[i + 1] == '\n') ? (i + 2) : (i + 1);
          if (fwrite(buf, 1, upto, stdout) != upto)
            return -1;
          return 0;
        }
      }
    }

    if (fwrite(buf, 1, upto, stdout) != upto)
      return -1;
  }

  return 0;
}

static void usage(const char *prog) {
  fprintf(stderr, "Usage: %s [-n N] FILE | -\n", prog);
}

int main(int argc, char **argv) {
  const char *prog = (argc > 0 && argv[0]) ? argv[0] : "head";
  long n = 10; // default

  int i = 1;
  while (i < argc && argv[i][0] == '-') {
    if (strcmp(argv[i], "-") == 0)
      break; // stdin sentinel
    if (strcmp(argv[i], "-n") == 0) {
      if (i + 1 >= argc) {
        usage(prog);
        return 2;
      }
      char *end = NULL;
      n = atoi(argv[i + 1]);
      if (end == argv[i + 1] || n <= 0) {
        fprintf(stderr, "%s: invalid line count: %s\n", prog, argv[i + 1]);
        return 2;
      }
      i += 2;
    } else {
      // Allow lone "-" handled later, otherwise unknown flag.
      if (strcmp(argv[i], "-") != 0) {
        usage(prog);
        return 2;
      }
      break;
    }
  }

  if (i >= argc) {
    usage(prog);
    return 2;
  }
  const char *path = argv[i];

  int rc = 0;
  if (strcmp(path, "-") == 0) {
    if (head_stream(stdin, (size_t)n) != 0) {
      fprintf(stderr, "%s: error reading stdin\n", prog);
      rc = 1;
    }
  } else {
    FILE *f = fopen(path, "rb");
    if (!f) {
      fprintf(stderr, "%s: cannot open '%s': %s\n", prog, path,
              strerror(errno));
      return 1;
    }
    rc = (head_stream(f, (size_t)n) == 0) ? 0 : 1;
    fclose(f);
  }

  return rc;
}
