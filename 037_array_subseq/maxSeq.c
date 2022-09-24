#include <stdio.h>
#include <stdlib.h>

int max(int x, int y) {
  if (x > y) {
    return x;
  }
  else {
    return y;
  }
}

size_t maxSeq(int * array, size_t n) {
  if (n == 1) {
    return 1;
  }
  if (array == NULL || n == 0) {
    return 0;
  }
  size_t max_seq = 1, count = 1;
  int * prev = &array[0];
  int * cur = &array[1];
  for (size_t i = 1; i < n; i++) {
    if (*cur > *prev) {
      count++;
      cur++;
      prev++;
      max_seq = max(max_seq, count);
    }
    else {
      count = 1;
      prev = cur;
      cur++;
    }
  }
  return max_seq;
}
