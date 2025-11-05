#include <stdarg.h>
#include <stdio.h>

static int is_space_char(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' ||
         c == '\v';
}

static int is_digit_char(char c) { return c >= '0' && c <= '9'; }

static void skip_space(const char **input) {
  while (**input && is_space_char(**input)) {
    (*input)++;
  }
}

static int read_signed(const char **input, long *out) {
  const char *s = *input;
  int sign = 1;

  if (*s == '+' || *s == '-') {
    if (*s == '-') {
      sign = -1;
    }
    s++;
  }

  if (!is_digit_char(*s)) {
    return 0;
  }

  long value = 0;
  while (is_digit_char(*s)) {
    value = value * 10 + (*s - '0');
    s++;
  }

  *input = s;
  *out = sign * value;
  return 1;
}

static int read_unsigned(const char **input, unsigned long *out) {
  const char *s = *input;
  if (!is_digit_char(*s)) {
    return 0;
  }

  unsigned long value = 0;
  while (is_digit_char(*s)) {
    value = value * 10 + (unsigned long)(*s - '0');
    s++;
  }

  *input = s;
  *out = value;
  return 1;
}

static int read_string(const char **input, char *dest) {
  const char *s = *input;
  if (*s == '\0') {
    return 0;
  }

  while (*s && !is_space_char(*s)) {
    if (dest) {
      *dest++ = *s;
    }
    s++;
  }

  if (dest) {
    *dest = '\0';
  }

  *input = s;
  return 1;
}

int sscanf(const char *str, const char *format, ...) {
  if (!str || !format) {
    return -1;
  }

  va_list ap;
  va_start(ap, format);

  const char *s = str;
  const char *f = format;
  int assigned = 0;

  while (*f) {
    if (is_space_char(*f)) {
      while (is_space_char(*f)) {
        f++;
      }
      skip_space(&s);
      continue;
    }

    if (*f != '%') {
      if (*s != *f) {
        break;
      }
      f++;
      if (*s) {
        s++;
      }
      continue;
    }

    f++; /* Skip '%' */
    if (*f == '%') {
      if (*s != '%') {
        break;
      }
      f++;
      if (*s) {
        s++;
      }
      continue;
    }

    int suppress = 0;
    if (*f == '*') {
      suppress = 1;
      f++;
    }

    while (*f == '-' || *f == '+' || *f == '0') {
      f++;
    }

    while (*f >= '0' && *f <= '9') {
      f++;
    }

    char length = 0;
    if (*f == 'l' || *f == 'h') {
      length = *f;
      f++;
    }

    char spec = *f ? *f++ : '\0';
    if (!spec) {
      break;
    }

    skip_space(&s);

    switch (spec) {
    case 'd': {
      long value;
      if (!read_signed(&s, &value)) {
        goto done;
      }
      if (!suppress) {
        if (length == 'l') {
          long *out = va_arg(ap, long *);
          *out = value;
        } else {
          int *out = va_arg(ap, int *);
          *out = (int)value;
        }
        assigned++;
      }
      break;
    }
    case 'u': {
      unsigned long value;
      if (!read_unsigned(&s, &value)) {
        goto done;
      }
      if (!suppress) {
        if (length == 'l') {
          unsigned long *out = va_arg(ap, unsigned long *);
          *out = value;
        } else {
          unsigned int *out = va_arg(ap, unsigned int *);
          *out = (unsigned int)value;
        }
        assigned++;
      }
      break;
    }
    case 's': {
      if (!suppress) {
        char *dest = va_arg(ap, char *);
        if (!read_string(&s, dest)) {
          goto done;
        }
        assigned++;
      } else {
        if (!read_string(&s, NULL)) {
          goto done;
        }
      }
      break;
    }
    case 'c': {
      if (*s == '\0') {
        goto done;
      }
      if (!suppress) {
        char *out = va_arg(ap, char *);
        *out = *s;
        assigned++;
      }
      s++;
      break;
    }
    default:
      /* Unsupported specifier: treat as failure. */
      goto done;
    }
  }

done:
  va_end(ap);
  return assigned;
}
