#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void breaker(FILE * f) {
  int charFreq[26];
  int c;
  for (int i = 0; i < 26; i++) {
    charFreq[i] = 0;
  }
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c = c - 'a';
      charFreq[c]++;
    }
    int suspect = 0;
    int maxfreq = 0;
    for (int i = 0; i < 26; i++) {
      if (maxfreq < charFreq[i]) {
        maxfreq = charFreq[i];
        suspect = i;
      }
    }
    if (maxfreq == 0) {
      fprintf(stderr, "Not letter in the file\n");
      exit(EXIT_FAILURE);
    }
    else if (suspect >= 4) {
      fprintf(stdout, "%d\n", suspect - 4);
    }
    else {
      fprintf(stdout, "%d\n", suspect + 22);
    }
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  breaker(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
