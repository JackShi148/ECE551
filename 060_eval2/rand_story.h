#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

struct storyContent_tag {
  char ** lines;
  size_t num;
};
typedef struct storyContent_tag storyContent;

//store the content of a file of categories and words into a catarry_t
catarray_t * getCatArray(char * fileName);
//compare the category in the line, if this category is in the cats, add its word
//else append this category into the cats
void compareName(catarray_t * cats, char * line);
//free all used cats
void freeCats(catarray_t * cats);
//check if underscores match each other and return the number of them
int checkUnderScore(char * line);
//parse the content of story and return replaced content
storyContent * parseTemp(storyContent * content);
//get the content of a story
storyContent * getContent(char * fileName);
//replace the blank parts
char * doReplace(char * line);
//print the content of a story
void printContent(storyContent * content);
//free all used content
void freeContent(storyContent * content);
#endif
