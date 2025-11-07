int main(void) { return -1; }
/*
#include <stdint.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/uptime.h>

#include <stdio.h>

#define SECONDS_PER_MINUTE 60U
#define SECONDS_PER_HOUR (60U * SECONDS_PER_MINUTE)
#define SECONDS_PER_DAY (24U * SECONDS_PER_HOUR)

static void write_string(const char *s) {
  while (*s) {
    putchar(*s++);
  }
}

static void write_unsigned(unsigned long value) {
  char buffer[20];
  int index = 0;

  if (value == 0) {
    putchar('0');
    return;
  }

  while (value > 0 && index < (int)(sizeof(buffer))) {
    buffer[index++] = (char)('0' + (value % 10));
    value /= 10;
  }

  while (index > 0) {
    putchar(buffer[--index]);
  }
}

static void write_two_digits(unsigned long value) {
  value %= 100;
  putchar('0' + (char)(value / 10));
  putchar('0' + (char)(value % 10));
}

static void write_load(int32_t load) {
  if (load < 0) {
    putchar('-');
    load = -load;
  }

  unsigned long integral = (unsigned long)(load / FSCALE);
  unsigned long remainder = (unsigned long)(load % FSCALE);
  unsigned long fractional =
      (unsigned long)((remainder * 100U + (FSCALE / 2)) / FSCALE);

  if (fractional >= 100) {
    integral += 1;
    fractional -= 100;
  }

  write_unsigned(integral);
  putchar('.');
  write_two_digits(fractional);
}

int main(void) {
  int32_t uptime_ticks = 0;
  int32_t loadavg[3] = {0, 0, 0};

  int result = suptime(&uptime_ticks, loadavg);
  if (result < 0) {
    write_string("uptime: failed to read system uptime\n");
    return EXIT_FAILURE;
  }

  if (uptime_ticks < 0) {
    uptime_ticks = 0;
  }

  unsigned long total_seconds = (unsigned long)(uptime_ticks / HZ);

  unsigned long days = total_seconds / SECONDS_PER_DAY;
  total_seconds %= SECONDS_PER_DAY;
  unsigned long hours = total_seconds / SECONDS_PER_HOUR;
  total_seconds %= SECONDS_PER_HOUR;
  unsigned long minutes = total_seconds / SECONDS_PER_MINUTE;
  unsigned long seconds = total_seconds % SECONDS_PER_MINUTE;

  write_string("uptime: ");
  if (days > 0) {
    write_unsigned(days);
    write_string("d ");
  }
  write_unsigned(hours);
  write_string("h ");
  write_unsigned(minutes);
  write_string("m ");
  write_unsigned(seconds);
  write_string("s | load average: ");
  write_load(loadavg[0]);
  putchar(' ');
  write_load(loadavg[1]);
  putchar(' ');
  write_load(loadavg[2]);
  putchar('\n');

  return EXIT_SUCCESS;
}
*/
