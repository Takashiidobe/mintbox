
#define BUFFER_SIZE 256

int main() { return -1; }

// #include <stdio.h>
// #include <stdlib.h>
// int main(int argc, char *argv[]) {
//   FILE *fp;
//   char buffer[BUFFER_SIZE];
//   size_t bytesRead;
//
//   if (argc == 1) {
//     fp = stdin;
//   } else {
//     fp = fopen(argv[1], "r");
//     if (fp == NULL) {
//       fprintf(stderr, "Error opening file");
//       return EXIT_FAILURE;
//     }
//   }
//
//   while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
//     fwrite(buffer, 1, bytesRead, stdout);
//   }
//
//   if (fp != stdin) {
//     fclose(fp);
//   }
//
//   return EXIT_SUCCESS;
// }
