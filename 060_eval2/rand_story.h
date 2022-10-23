#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

struct storyContent_tag {
  char ** lines;
  size_t num;
};
typedef struct storyContent_tag storyContent;

//maintain the order of used words in the category which contains used words
//n is the reference used in the blank
//return the corrresponding word based on reference
const char * maintainUsedWords(category_t * cat, size_t n);
//check if the newWord is in the used words
//if not in, add this new word into used words list
void addUsedWords(category_t * cat, const char * newWord);
//free the memory used by usedWords list
void freeCategory(category_t * usedWords);
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
storyContent * parseTemp(storyContent * content, catarray_t * cats);
//get the content of a story
storyContent * getContent(char * fileName);
//replace the blank parts with the catarray_t
char * doReplace(char * line, catarray_t * cats, category_t * usedWords);
//print the content of a story
void printContent(storyContent * content);
//free all used content
void freeContent(storyContent * content);
#endif
