#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    while (1) {
      puts("y");
    }
  }

  while (1) {
    puts(argv[1]);
  }
}
