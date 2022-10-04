#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void run(FILE * f) {
  char ** lines = malloc(sizeof(*lines));
  if (lines == NULL) {
    perror("there is no available space\n");
  }
  char * line = NULL;
  size_t sz = 0;
  size_t lineNum = 0;
  while (getline(&line, &sz, f) >= 0) {
    lines = realloc(lines, (lineNum + 1) * sizeof(*lines));
    lines[lineNum] = line;
    lineNum++;
    line = NULL;  //assign a new address
  }
  sortData(lines, lineNum);
  for (size_t i = 0; i < lineNum; i++) {
    printf("%s", lines[i]);
    free(lines[i]);
  }
  free(lines);
  free(line);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  FILE * f = NULL;
  if (argc == 1) {
    f = stdin;
    if (f == NULL) {
      perror("Cannot read standard input\n");
      return EXIT_FAILURE;
    }
    run(f);
  }
  else {
    for (int i = 1; i < argc; i++) {
      f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Cannot open input file(s)\n");
        return EXIT_FAILURE;
      }
      run(f);
      if (fclose(f) != 0) {
        fprintf(stderr, "the file %s cannot be closed\n", argv[i]);
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
