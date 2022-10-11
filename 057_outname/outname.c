#include "outname.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * suffix = ".counts";
  size_t len = strlen(inputName) + strlen(suffix) + 1;
  char * outputName = strdup(inputName);
  outputName = realloc(outputName, len * sizeof(*outputName));
  assert(outputName != NULL);
  outputName = strcat(outputName, suffix);
  return outputName;
}
