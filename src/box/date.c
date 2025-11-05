#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

static const int SECONDS_PER_MINUTE = 60;
static const int SECONDS_PER_HOUR = 60 * SECONDS_PER_MINUTE;
static const int SECONDS_PER_DAY = 24 * SECONDS_PER_HOUR;

static int is_leap_year(int year) {
  if ((year % 4) != 0) {
    return 0;
  }
  if ((year % 100) != 0) {
    return 1;
  }
  return (year % 400) == 0;
}

static int days_in_year(int year) { return is_leap_year(year) ? 366 : 365; }

static int days_in_month(int year, int month) {
  static const int month_lengths[] = {31, 28, 31, 30, 31, 30,
                                      31, 31, 30, 31, 30, 31};
  if (month == 2 && is_leap_year(year)) {
    return 29;
  }
  return month_lengths[month - 1];
}

static void epoch_to_components(time_t seconds, int *year, int *month, int *day,
                                int *hour, int *minute, int *second) {
  long long total_days = seconds / SECONDS_PER_DAY;
  long long remainder = seconds % SECONDS_PER_DAY;

  if (remainder < 0) {
    remainder += SECONDS_PER_DAY;
    total_days -= 1;
  }

  *hour = (int)(remainder / SECONDS_PER_HOUR);
  remainder %= SECONDS_PER_HOUR;
  *minute = (int)(remainder / SECONDS_PER_MINUTE);
  *second = (int)(remainder % SECONDS_PER_MINUTE);

  int current_year = 1970;
  while (total_days >= days_in_year(current_year)) {
    total_days -= days_in_year(current_year);
    current_year++;
  }
  while (total_days < 0) {
    current_year--;
    total_days += days_in_year(current_year);
  }

  int current_month = 1;
  while (1) {
    int dim = days_in_month(current_year, current_month);
    if (total_days < dim) {
      break;
    }
    total_days -= dim;
    current_month++;
  }

  *year = current_year;
  *month = current_month;
  *day = (int)total_days + 1;
}

static void write_padded_unsigned(int value, int digits) {
  int divisor = 1;
  for (int i = 1; i < digits; ++i) {
    divisor *= 10;
  }

  for (int i = 0; i < digits; ++i) {
    int digit = (value / divisor) % 10;
    putchar('0' + digit);
    divisor /= 10;
  }
}

int main(void) {
  struct timeval tv;
  struct timezone tz = {0, 0};

  if (gettimeofday(&tv, &tz) != 0) {
    puts("date: failed to read current time");
    return EXIT_FAILURE;
  }

  time_t local_seconds = tv.tv_sec;
  local_seconds -= (time_t)tz.tz_minuteswest * SECONDS_PER_MINUTE;
  if (tz.tz_dsttime > 0) {
    local_seconds += SECONDS_PER_HOUR;
  }

  int year, month, day, hour, minute, second;
  epoch_to_components(local_seconds, &year, &month, &day, &hour, &minute,
                      &second);

  write_padded_unsigned(year, 4);
  putchar('-');
  write_padded_unsigned(month, 2);
  putchar('-');
  write_padded_unsigned(day, 2);
  putchar(' ');
  write_padded_unsigned(hour, 2);
  putchar(':');
  write_padded_unsigned(minute, 2);
  putchar(':');
  write_padded_unsigned(second, 2);
  putchar('.');
  write_padded_unsigned(tv.tv_usec, 6);
  putchar('\r');
  putchar('\n');

  return EXIT_SUCCESS;
}
