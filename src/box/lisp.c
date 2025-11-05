/* mini_lisp_add_repl_no_ungetc.c
 * Minimal Lisp REPL for Atari MiNT (mintlib), supporting only (+ ...).
 */
#include <ctype.h>
#include <stdio.h>

static int have_peek = 0;
static int peek_ch = 0;

static int read_raw(void) {
  int c = fgetc(stdin);
  return (c == EOF) ? EOF : c;
}
static int peekc(void) {
  if (!have_peek) {
    peek_ch = read_raw();
    have_peek = 1;
  }
  return peek_ch;
}
static int getc1(void) {
  int c = peekc();
  have_peek = 0; /* consume it */
  return c;
}

static void skip_ws(void) {
  int c;
  for (;;) {
    c = peekc();
    if (c == -1)
      return;
    if (c == ';') { /* Lisp comment to end of line */
      do {
        c = getc1();
      } while (c != '\n' && c != -1);
      continue;
    }
    if (!isspace(c))
      return;
    (void)getc1();
  }
}

/* Forward decl */
static int parse_expr(long *out);

static int parse_number(long *out) {
  skip_ws();
  int c = peekc();
  int neg = 0;

  if (c == '+' || c == '-') {
    neg = (c == '-');
    (void)getc1(); /* consume sign */
    int d = peekc();
    if (!isdigit(d)) { /* not a number after sign -> fail */
      /* Put no characters back: caller will handle failure. */
      return 0;
    }
  } else if (!isdigit(c)) {
    return 0;
  }

  long val = 0;
  int any = 0;
  while (isdigit(peekc())) {
    int d = getc1();
    val = val * 10 + (d - '0'); /* no overflow handling (kept minimal) */
    any = 1;
  }
  if (!any)
    return 0;
  *out = neg ? -val : val;
  return 1;
}

/* Parse a list that starts with '(' already consumed; only (+ expr*) ')' */
static int parse_list(long *out) {
  skip_ws();
  int c = peekc();
  if (c != '+') {
    fprintf(stderr, "error: only '+' is supported in lists\n");
    return 0;
  }
  (void)getc1(); /* consume '+' */

  long sum = 0;
  for (;;) {
    skip_ws();
    c = peekc();
    if (c == EOF) {
      fprintf(stderr, "error: unexpected EOF inside list\n");
      return 0;
    }
    if (c == ')') {
      (void)getc1(); /* consume ')' */
      *out = sum;
      return 1;
    }
    long v;
    if (!parse_expr(&v))
      return 0;
    sum += v;
  }
}

/* expr := number | '(' '+' {expr} ')' */
static int parse_expr(long *out) {
  skip_ws();
  int c = peekc();
  if (c == EOF)
    return 0;
  if (c == '(') {
    (void)getc1(); /* consume '(' */
    return parse_list(out);
  }
  if (parse_number(out))
    return 1;

  fprintf(stderr, "error: expected number or '(+ ... )'\n");
  return 0;
}

static void discard_line(void) {
  int c;
  do {
    c = getc1();
  } while (c != '\n' && c != EOF);
}

int main(void) {
  for (;;) {
    fputs("> ", stdout);
    fflush(stdout);

    /* If immediate EOF, exit cleanly */
    if (peekc() == EOF)
      break;

    long result;
    if (parse_expr(&result)) {
      /* consume trailing spaces and at most one newline for neat output */
      skip_ws();
      if (peekc() == '\n')
        (void)getc1();
      printf("%ld\n", result);
    } else {
      /* on error, resync to end of line */
      discard_line();
    }
  }
  return 0;
}
