#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static unsigned long value_to_unsigned(long value) {
  if (value < 0) {
    return (unsigned long)(-(value + 1)) + 1UL;
  }
  return (unsigned long)value;
}

static size_t format_unsigned(unsigned long value, char *buf) {
  char tmp[32];
  size_t len = 0;

  do {
    tmp[len++] = (char)('0' + (value % 10));
    value /= 10;
  } while (value != 0);

  for (size_t i = 0; i < len; i++) {
    buf[i] = tmp[len - 1 - i];
  }
  return len;
}

static size_t format_signed(long value, char *buf) {
  size_t idx = 0;
  if (value < 0) {
    buf[idx++] = '-';
  }
  idx += format_unsigned(value_to_unsigned(value), buf + idx);
  return idx;
}

static void append_buffer(char c, char *dest, size_t size, size_t *stored,
                          size_t *total) {
  if (*total < SIZE_MAX) {
    (*total)++;
  }

  if (size == 0) {
    return;
  }

  if (*stored < size - 1) {
    dest[(*stored)++] = c;
  }
}

static void append_string(const char *src, size_t len, char *dest, size_t size,
                          size_t *stored, size_t *total) {
  for (size_t i = 0; i < len; i++) {
    append_buffer(src[i], dest, size, stored, total);
  }
}

int vsnprintf(char *str, size_t size, const char *format, va_list ap) {
  size_t stored = 0;
  size_t total = 0;

  if (!format) {
    return -1;
  }

  while (*format) {
    if (*format != '%') {
      append_buffer(*format, str, size, &stored, &total);
      format++;
      continue;
    }

    format++; /* Skip '%' */
    if (*format == '\0') {
      append_buffer('%', str, size, &stored, &total);
      break;
    }

    if (*format == '%') {
      append_buffer('%', str, size, &stored, &total);
      format++;
      continue;
    }

    /* Parse flags we don't support but must skip. */
    while (*format == '-' || *format == '+' || *format == ' ' ||
           *format == '#' || *format == '0') {
      format++;
    }

    /* Field width (ignored). */
    while (*format >= '0' && *format <= '9') {
      format++;
    }

    int precision = -1;
    if (*format == '.') {
      format++;
      precision = 0;
      while (*format >= '0' && *format <= '9') {
        precision = precision * 10 + (*format - '0');
        format++;
      }
    }

    char length = 0;
    if (*format == 'l' || *format == 'h' || *format == 'z') {
      length = *format;
      format++;
      if (length == 'l' && *format == 'l') {
        /* Treat %ll like %l for our purposes. */
        format++;
      }
    }

    char spec = *format ? *format++ : '\0';
    if (!spec) {
      append_buffer('%', str, size, &stored, &total);
      break;
    }

    switch (spec) {
    case 'c': {
      int value = va_arg(ap, int);
      append_buffer((char)value, str, size, &stored, &total);
      break;
    }
    case 'd':
    case 'i': {
      long value = (length == 'l') ? va_arg(ap, long) : va_arg(ap, int);
      char buf[32];
      size_t len = format_signed(value, buf);
      append_string(buf, len, str, size, &stored, &total);
      break;
    }
    case 'u': {
      unsigned long value =
          (length == 'l') ? va_arg(ap, unsigned long)
                          : (unsigned long)va_arg(ap, unsigned int);
      char buf[32];
      size_t len = format_unsigned(value, buf);
      append_string(buf, len, str, size, &stored, &total);
      break;
    }
    case 's': {
      const char *s = va_arg(ap, const char *);
      if (!s) {
        s = "(null)";
      }
      size_t len = strlen(s);
      if (precision >= 0 && (size_t)precision < len) {
        len = (size_t)precision;
      }
      append_string(s, len, str, size, &stored, &total);
      break;
    }
    default:
      /* Unsupported specifier: emit it verbatim. */
      append_buffer('%', str, size, &stored, &total);
      append_buffer(spec, str, size, &stored, &total);
      break;
    }
  }

  if (size > 0 && str) {
    if (stored >= size) {
      stored = size - 1;
    }
    str[stored] = '\0';
  }

  if (total > (size_t)INT_MAX) {
    return -1;
  }
  return (int)total;
}

int snprintf(char *str, size_t size, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = vsnprintf(str, size, format, ap);
  va_end(ap);
  return result;
}
