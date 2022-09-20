#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void test_Maxseq(int * array, size_t n, size_t ans_expected) {
  if (maxSeq(array, n) != ans_expected) {
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int a1[5] = {1, 2, 3, 2, 4};
  int a2[1] = {0};
  int a3[3] = {0, 0, 0};
  int a4[2] = {1, 0};
  int a5[3] = {-1, 0, -1};
  int a6[] = {-101, -23, 2, 3, 5, 5, -2, -1, 5, 7, 8};
  test_Maxseq(a1, 0, 0);
  test_Maxseq(a1, 5, 3);
  test_Maxseq(a2, 1, 1);
  test_Maxseq(a3, 3, 1);
  test_Maxseq(a4, 2, 1);
  test_Maxseq(a5, 3, 2);
  test_Maxseq(&a6[1], 3, 3);
  test_Maxseq(&a6[2], 8, 4);
  test_Maxseq(&a6[2], 5, 3);
  test_Maxseq(NULL, 0, 0);
  printf("passing all the testcases\n");
  return EXIT_SUCCESS;
}
