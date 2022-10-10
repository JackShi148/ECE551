#include "kv.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void splitKV(kvpair_t * kvpair, const char * line) {
  char * equal = strchr(line, '=');
  assert(equal != NULL);
  size_t key_len = equal - line;
  kvpair->key = strndup(line, key_len);
  size_t value_len = 0;
  char * newLine = strchr(equal + 1, '\n');
  if (newLine != NULL) {
    value_len = newLine - equal - 1;
    kvpair->value = strndup(equal + 1, value_len);
  }
  else {
    kvpair->value = strdup(equal + 1);
  }
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  assert(f != NULL);
  //initialize pairs
  kvarray_t * pairs = malloc(sizeof(*pairs));
  assert(pairs != NULL);
  //initialize kvpair
  pairs->kvpairs = malloc(sizeof(*pairs->kvpairs));
  assert(pairs->kvpairs);
  pairs->lenght = 0;
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    pairs->lenght++;
    pairs->kvpairs = realloc(pairs->kvpairs, pairs->lenght * sizeof(*pairs->kvpairs));
    splitKV(&pairs->kvpairs[pairs->lenght - 1], line);
    free(line);
    line = NULL;
  }
  //free the last line from getline
  free(line);
  //close file
  fclose(f);
  return pairs;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->lenght; i++) {
    free(pairs->kvpairs[i].key);
    free(pairs->kvpairs[i].value);
  }
  free(pairs->kvpairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->lenght; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvpairs[i].key, pairs->kvpairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->lenght; i++) {
    if (strcmp(pairs->kvpairs[i].key, key) == 0) {
      return pairs->kvpairs[i].value;
    }
  }
  return NULL;
}
