#include "pandemic.h"

#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  char * commaPos = strchr(line, ',');
  //find comma
  if (*commaPos == '\0') {
    printf("invalid input: no comma\n");
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
  if (i == 64) {
    printf("invalid input: the name is too long\n");
    exit(EXIT_FAILURE);
  }
  else {
    ans.name[i] = '\0';
    i++;
  }
  //no population is an error
  if (line[i] == '\0') {
    printf("invalid input: no population\n");
    exit(EXIT_FAILURE);
  }
  char * population = &line[i];
  char * end;
  ans.population = strtol(population, &end, 10);
  /*if (*end != '\0' && strcmp(population, "Population") != 0) {
    printf("invalid input: invalid population\n");
    exit(EXIT_FAILURE);
  }*/
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  //check parameters
  if (data == NULL || n_days < 7) {
    printf("invalid parameter: parameter doesn't meet requirements\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < n_days - 6; i++) {
    double sum = 0.0;
    for (size_t j = i; j < i + 7; j++) {
      sum = sum + data[j];
    }
    avg[i] = sum / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  //check input
  if (data == NULL || n_days <= 0) {
    printf("invalid parameter: parameter doesn't meet requirements\n");
    exit(EXIT_FAILURE);
  }
  double caseNum = 0.0;
  for (size_t i = 0; i < n_days; i++) {
    caseNum = caseNum + data[i];
    cum[i] = (caseNum / pop) * 100000;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  if (countries == NULL || data == NULL || n_countries < 0 || n_days < 0) {
    printf("invalid input: parameter doesn't meet requirments\n");
    exit(EXIT_FAILURE);
  }
  for (size_t j = 0; j < n_days; j++) {
    unsigned maxCaseNum = data[0][j];
    char * country_name = countries[0].name;
    for (size_t i = 1; i < n_countries; i++) {
      if (maxCaseNum < data[i][j]) {
        maxCaseNum = data[i][j];
        country_name = countries[i].name;
      }
    }
    printf("%s has the most daily cases with %u\n", country_name, maxCaseNum);
  }
}
