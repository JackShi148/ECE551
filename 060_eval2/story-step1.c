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
  storyContent * content = getContent(argv[1]);
  storyContent * newContent = parseTemp(content, NULL, argv[1]);
  printContent(newContent);
  freeContent(content);
  freeContent(newContent);
  return EXIT_SUCCESS;
}
