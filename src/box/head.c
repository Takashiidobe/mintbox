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

#define BUFSZ 4096

static int head_stream(FILE *fp, size_t max_lines) {
  char buf[BUFSZ];
  size_t lines = 0;

  while (lines < max_lines && fgets(buf, sizeof(buf), fp)) {
    if (fputs(buf, stdout) == EOF)
      return -1;

    if (strchr(buf, '\n') != NULL)
      lines++;
  }

  return ferror(fp) ? -1 : 0;
}

static int print_header(const char *name, int first) {
  if (!first)
    putchar('\n');                      /* blank line between files */
  if (printf("==> %s <==\n", name) < 0) /* header */
    return -1;
  return 0;
}

int main(int argc, char **argv) {
  long n = 10;
  int argi = 1;
  int status = 0;

  /* Minimal "-n N" handling (e.g., head -n 25 file). */
  if (argi + 1 < argc && strcmp(argv[argi], "-n") == 0) {
    char *end = NULL;
    int v = atoi(argv[argi + 1]);
    if (!end || *end != '\0') {
      fprintf(stderr, "head: invalid number: %s\n", argv[argi + 1]);
      return 2;
    }
    n = v;
    argi += 2;
  }

  int files = argc - argi;
  if (files <= 0) {
    /* stdin */
    if (head_stream(stdin, n) < 0) {
      perror("head: read error");
      return 1;
    }
    return 0;
  }

  int first = 1;
  for (; argi < argc; ++argi) {
    const char *name = argv[argi];
    FILE *fp = NULL;

    if (strcmp(name, "-") == 0) {
      fp = stdin;
    } else {
      fp = fopen(name, "rb");

      if (!fp) {
        fprintf(stderr, "head: cannot open '%s': %s\n", name, strerror(errno));
        status = 1;
        continue;
      }
    }

    if (files > 1) {
      if (print_header(name, first) < 0) {
        status = 1;
      }
      first = 0;
    }

    if (head_stream(fp, n) < 0) {
      fprintf(stderr, "head: read error on '%s'\n", name);
      status = 1;
    }

    if (fp != stdin)
      fclose(fp);
  }

  return status;
}
