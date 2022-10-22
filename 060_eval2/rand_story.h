#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

struct storyContent_tag {
  char ** lines;
  size_t num;
};
typedef struct storyContent_tag storyContent;

//any functions you want your main to use
int checkUnderScore(char * line);
storyContent * parseTemp(storyContent * content);
storyContent * getContent(char * fileName);
char * doReplace(char * line);
void printContent(storyContent * content);
void freeSpace(storyContent * content);
#endif
