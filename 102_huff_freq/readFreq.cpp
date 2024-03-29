#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * array = new uint64_t[257]();
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    std::cerr << "fail to open file" << std::endl;
    exit(EXIT_FAILURE);
  }
  int t;
  while ((t = fgetc(f)) != EOF) {
    array[t]++;
  }
  array[256] = 1;
  if (fclose(f) != 0) {
    std::cerr << "fail to close fiel" << std::endl;
    exit(EXIT_FAILURE);
  }
  return array;
}
