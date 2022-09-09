#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  for (int i = 1; i <= working.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n", startAge / 12, startAge % 12, initial);
    initial += initial * working.rate_of_return + working.contribution;
    startAge++;
  }
  for (int i = 1; i <= retired.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n", startAge / 12, startAge % 12, initial);
    initial += initial * retired.rate_of_return + retired.contribution;
    startAge++;
  }
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  retirement(327, 21345, working, retired);
  return EXIT_SUCCESS;
}
