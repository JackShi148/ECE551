#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(FILE * f) {
  char rotated[10][10];
  char line[11];
  int lineNum = 0;
  while (fgets(line, 12, f) != NULL) {  // size == 12 for the space for '\0'
    lineNum++;
    if (lineNum > 10) {
      fprintf(stderr, "the number of row is more than 10\n");
      exit(EXIT_FAILURE);
    }
    if (strchr(line, '\n') == NULL) {
      fprintf(stderr, "the %dth row of matrix has no newline sign\n", lineNum);
      exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 10; i++) {
      rotated[i][10 - lineNum] = line[i];
    }
  }
  if (lineNum < 10) {
    fprintf(stderr, "the number of row is less than 10\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout, "%c", rotated[i][j]);
    }
    fprintf(stdout, "\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "the number of argc is not 2n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }
  rotate(f);
  if (fclose(f) != 0) {
    perror("fclose");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
