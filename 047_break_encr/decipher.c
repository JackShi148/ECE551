#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void decipher(FILE * f) {
  int charFreq[26];
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      charFreq[c - 'a']++;
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
    else if (4 <= suspect && suspect <= 25) {
      fprintf(stdout, "%d\n", suspect - 4);
    }
    else if (0 <= suspect && suspect <= 3) {
      fprintf(stdout, "%d\n", suspect + 22);
    }
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "the number of arguments is wrong\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file\n");
    return EXIT_FAILURE;
  }
  decipher(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
