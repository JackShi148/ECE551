#include "counts.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * cts = malloc(sizeof(*cts));
  assert(cts != NULL);
  cts->counts = NULL;
  cts->length = 0;
  cts->num_unknown = 0;
  return cts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->num_unknown++;
    return;
  }
  for (int i = 0; i < c->length; i++) {
    if (strcmp(name, c->counts[i].name) == 0) {
      c->counts[i].freq++;
      return;
    }
  }
  c->length++;
  c->counts = realloc(c->counts, c->length * sizeof(*c->counts));
  c->counts[c->length - 1].freq = 1;
  c->counts[c->length - 1].name = strdup(name);
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->length; i++) {
    fprintf(outFile, "%s : %d\n", c->counts[i].name, c->counts[i].freq);
  }
  if (c->num_unknown != 0) {
    fprintf(outFile, "<unknown> : %d\n", c->num_unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->length; i++) {
    free(c->counts[i].name);
  }
  free(c->counts);
  free(c);
}
