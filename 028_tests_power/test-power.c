#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void check_power(unsigned x, unsigned y, unsigned expected_value) {
  if (power(x, y) != expected_value) {
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  check_power(0, 0, 1);
  check_power(4, 0, 1);
  check_power(0, 6, 0);
  check_power(2, 3, 8);
  check_power(4290000000, 1, 4290000000);
  check_power(1, 10, 1);
  return EXIT_SUCCESS;
}
