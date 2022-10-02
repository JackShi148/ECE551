#include "pandemic.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  char * commaPos = strchr(line, ',');
  //find comma
  if (commaPos == NULL) {
    fprintf(stderr, "invalid input: no comma\n");
    exit(EXIT_FAILURE);
  }
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;
  //get name
  int i = 0;
  while (line[i] != ',' && i < 64) {
    ans.name[i] = line[i];
    i++;
  }
  //check space for '\0'
  if (i == 64) {
    fprintf(stderr, "invalid input: the name is too long\n");
    exit(EXIT_FAILURE);
  }
  else {
    ans.name[i] = '\0';
    i++;
  }
  //no population is an error
  if (line[i] == '\0' || line[i] == '\n') {
    fprintf(stderr, "invalid input: population needed\n");
    exit(EXIT_FAILURE);
  }
  char * population = &line[i];
  char * end;
  //check if population overflows
  ans.population = strtoull(population, &end, 10);
  if (errno == ERANGE) {
    perror("invalid population");
    exit(EXIT_FAILURE);
  }
  //check if population contains non-numberic characters
  if (*end != '\0') {
    if (*end != '\n') {
      fprintf(stderr, "invalid input: population is invalid\n");
      exit(EXIT_FAILURE);
    }
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //check parameters
  if (data == NULL || n_days < 7) {
    fprintf(stderr, "invalid parameter: parameter doesn't meet requirements\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < n_days - 6; i++) {
    double sum = 0.0;
    unsigned * pos = &data[i];
    for (size_t j = 0; j < 7; j++) {
      //check whether the number of data matches with n_days
      if (pos == NULL) {
        fprintf(stderr, "error: the number of data doesn't match with n_days\n");
        exit(EXIT_FAILURE);
      }
      sum = sum + *pos;
      pos = pos + 1;
    }
    avg[i] = sum / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //check parameters
  if (data == NULL || n_days < 0) {
    fprintf(stderr, "invalid parameter: parameter doesn't meet requirements\n");
    exit(EXIT_FAILURE);
  }
  double caseNum = 0.0;
  unsigned * pos = &data[0];
  for (size_t i = 0; i < n_days; i++) {
    //check whether the number of data matches with n_days
    if (pos == NULL) {
      fprintf(stderr, "error: the number of data doesn't match with n_days\n");
      exit(EXIT_FAILURE);
    }
    caseNum = caseNum + *pos;
    cum[i] = (caseNum / pop) * 100000;
    pos = pos + 1;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //check parameters
  if (countries == NULL || data == NULL || n_countries < 0 || n_days < 0) {
    fprintf(stderr, "invalid parameter: parameter doesn't meet requirments\n");
    exit(EXIT_FAILURE);
  }
  unsigned maxCaseNum = data[0][0];
  char * country_name = countries[0].name;
  for (size_t j = 0; j < n_days; j++) {
    for (size_t i = 0; i < n_countries; i++) {
      if (maxCaseNum < data[i][j]) {
        maxCaseNum = data[i][j];
        country_name = countries[i].name;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", country_name, maxCaseNum);
}
