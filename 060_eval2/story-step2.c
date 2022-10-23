#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "the number of arguments should be 2\n");
    return EXIT_FAILURE;
  }
  catarray_t * cats = getCatArray(argv[1]);
  printWords(cats);
  freeCats(cats);
  return EXIT_SUCCESS;
}
