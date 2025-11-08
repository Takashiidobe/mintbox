#include <stdlib.h>

static void swap(char *a, char *b, size_t size) {
  if (a == b)
    return;
  while (size--) {
    char tmp = a[size];
    a[size] = b[size];
    b[size] = tmp;
  }
}

static void qsort_impl(char *base, size_t nmemb, size_t size,
                       int (*compar)(const void *, const void *)) {
  if (nmemb < 2)
    return;

  size_t pivot_index = nmemb / 2;
  char *last = base + (nmemb - 1) * size;
  swap(base + pivot_index * size, last, size);

  size_t store = 0;
  for (size_t i = 0; i < nmemb - 1; i++) {
    char *elem = base + i * size;
    if (compar(elem, last) < 0) {
      swap(elem, base + store * size, size);
      store++;
    }
  }

  swap(base + store * size, last, size);

  qsort_impl(base, store, size, compar);
  qsort_impl(base + (store + 1) * size, nmemb - store - 1, size, compar);
}

void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *)) {
  if (!base || nmemb < 2 || size == 0 || !compar)
    return;

  qsort_impl((char *)base, nmemb, size, compar);
}
