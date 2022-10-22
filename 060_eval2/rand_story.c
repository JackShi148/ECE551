#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
int checkUnderScore(char * line) {
  char * ptr = line;
  int count = 0;
  ptr = strchr(ptr, '_');
  while (ptr != NULL) {
    count++;
    if (*(ptr + 1) == '\0') {
      break;
    }
    else {
      ptr = strchr(ptr + 1, '_');
    }
  }
  if (count % 2 == 0) {
    return count;
  }
  return -1;
}

storyContent * getContent(char * fileName) {
  FILE * f = fopen(fileName, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open %s\n", fileName);
    exit(EXIT_FAILURE);
  }
  char * line = NULL;
  size_t sz = 0;
  storyContent * content = malloc(sizeof(*content));
  content->lines = NULL;
  content->num = 0;
  while (getline(&line, &sz, f) >= 0) {
    content->num++;
    content->lines = realloc(content->lines, content->num * sizeof(*content->lines));
    content->lines[content->num - 1] = line;
    line = NULL;
  }
  free(line);
  int a = fclose(f);
  if (a != 0) {
    fprintf(stderr, "Cannot close %s\n", fileName);
    exit(EXIT_FAILURE);
  }
  return content;
}

storyContent * parseTemp(storyContent * content) {
  storyContent * newContent = malloc(sizeof(*newContent));
  newContent->lines = NULL;
  newContent->num = 0;
  for (size_t i = 0; i < content->num; i++) {
    newContent->num++;
    newContent->lines =
        realloc(newContent->lines, newContent->num * sizeof(*newContent->lines));
    newContent->lines[newContent->num - 1] = doReplace(content->lines[i]);
  }
  return newContent;
}

void printContent(storyContent * content) {
  for (size_t i = 0; i < content->num; i++) {
    printf("%s", content->lines[i]);
  }
}

char * doReplace(char * line) {
  int num_udscr = checkUnderScore(line);
  if (num_udscr == -1) {
    fprintf(stderr, "underscores don't match each other\n");
    exit(EXIT_FAILURE);
  }
  if (num_udscr == 0) {
    return line;
  }
  char ** ptrs = malloc(num_udscr * sizeof(*ptrs));
  ptrs[0] = strchr(line, '_');
  for (int i = 1; i < num_udscr; i++) {
    ptrs[i] = strchr(ptrs[i - 1] + 1, '_');
  }
  int len = ptrs[0] - line;
  char * newLine = strndup(line, len);
  for (int i = 1; i < num_udscr; i++) {
    if (i % 2 == 0) {
      len = ptrs[i] - ptrs[i - 1] - 1;
      //plus 1 for '\0'
      newLine = realloc(newLine, (strlen(newLine) + len + 1) * sizeof(*newLine));
      newLine = strncat(newLine, ptrs[i - 1] + 1, len);
    }
    else {
      len = ptrs[i] - ptrs[i - 1] - 1;
      char * catgry = strndup(ptrs[i - 1] + 1, len);
      const char * str = chooseWord(catgry, NULL);
      free(catgry);
      //plus 1 for '\0'
      newLine = realloc(newLine, (strlen(newLine) + strlen(str) + 1) * sizeof(*newLine));
      newLine = strcat(newLine, str);
    }
  }
  if (*ptrs[num_udscr - 1] + 1 != '\0') {
    //plus 1 for '\0'
    newLine = realloc(
        newLine,
        (strlen(newLine) + strlen(ptrs[num_udscr - 1] + 1) + 1) * sizeof(*newLine));
    newLine = strcat(newLine, ptrs[num_udscr - 1] + 1);
  }
  free(ptrs);
  return newLine;
}

void freeSpace(storyContent * content) {
  for (size_t i = 0; i < content->num; i++) {
    free(content->lines[i]);
  }
  free(content->lines);
  free(content);
}
