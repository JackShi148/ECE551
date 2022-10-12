#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t * c = createCounts();
  FILE * f = fopen(filename, "r");
  assert(f != NULL);
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    char * t = NULL;
    char * newLine = strchr(line, '\n');
    if (newLine != NULL) {
      t = strndup(line, newLine - line);
    }
    else {
      t = strdup(line);
    }
    addCount(c, lookupValue(kvPairs, t));
    free(line);
    free(t);
    line = NULL;
  }
  free(line);
  int r = fclose(f);
  assert(r == 0);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "need at least 3 args\n");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      fprintf(stderr, "Fail to open the file %s\n", outName);
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    int r = fclose(f);
    if (r != 0) {
      fprintf(stderr, "Fail to close the file %s\n", outName);
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
    //free the memory for kv
    freeKVs(kv);
    return EXIT_SUCCESS;
  }
}
