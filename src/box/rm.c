#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  if (remove(argv[1]) == 0) {
    return 0;
  } else {
    return 1;
  }
}
