#include <ctype.h>
#include <errno.h>

#include <cstdlib>
#include <sstream>
#include <vector>

#include "page.hpp"

void chooseStory(std::vector<Page *> & pages) {
  size_t cur_page = 0;
  while (true) {
    pages[cur_page]->printContentandChoice();
    if (pages[cur_page]->getType() == 'W' || pages[cur_page]->getType() == 'L') {
      break;
    }
    std::vector<size_t> des_pageNums = pages[cur_page]->getDesNums();
    size_t choices_len = pages[cur_page]->getChoiceSize();
    bool validChoice = false;
    while (!validChoice) {
      std::string input;
      std::getline(std::cin, input);
      char * end = NULL;
      size_t choice_num = strtoull(input.c_str(), &end, 10);
      if (errno == ERANGE) {
        std::cout << "That is not a valid choice, please try again" << std::endl;
        continue;
      }
      if (*end != '\0') {
        std::cout << "That is not a valid choice, please try again" << std::endl;
        continue;
      }
      if (choice_num == 0 || choice_num > choices_len) {
        std::cout << "That is not a valid choice, please try again" << std::endl;
        continue;
      }
      cur_page = des_pageNums[choice_num - 1];
      validChoice = true;
    }
  }
}
