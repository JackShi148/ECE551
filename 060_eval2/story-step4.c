#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc > 4 || argc < 3) {
    fprintf(stderr, "the number of arguments is incorrect\n");
    return EXIT_FAILURE;
  }
  if (argc == 3) {
    catarray_t * cats = getCatArray(argv[1]);
    storyContent * content = getContent(argv[2]);
    storyContent * newContent = parseTemp(content, cats, argv[1]);
    printContent(newContent);
    freeContent(content);
    freeContent(newContent);
    freeCats(cats);
  }
  else {
    char * option = argv[1];
    catarray_t * cats = getCatArray(argv[2]);
    storyContent * content = getContent(argv[3]);
    storyContent * newContent = parseTemp(content, cats, option);
    printContent(newContent);
    freeContent(content);
    freeContent(newContent);
    freeCats(cats);
  }
  return EXIT_SUCCESS;
}
