#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "the number of arguments should be 3\n");
    return EXIT_FAILURE;
  }
  catarray_t * cats = getCatArray(argv[1]);
  storyContent * content = getContent(argv[2]);
  storyContent * newContent = parseTemp(content, cats);
  printContent(newContent);
  freeContent(content);
  freeContent(newContent);
  freeCats(cats);
  return EXIT_SUCCESS;
}
