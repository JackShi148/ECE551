#ifndef __STORY_HPP__
#define __STORY_HPP__
#include <ctype.h>
#include <errno.h>

#include <cstdlib>
#include <sstream>
#include <stack>
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

bool inVisited(std::vector<size_t> & visited, size_t target) {
  int len = visited.size();
  for (int i = 0; i < len; i++) {
    if (visited[i] == target) {
      return true;
    }
  }
  return false;
}

void dfsFindPath(std::vector<Page *> & pages,
                 std::vector<std::vector<size_t> > & paths,
                 std::vector<std::vector<size_t> > & choices) {
  std::stack<std::vector<size_t> > stack_paths;
  std::stack<std::vector<size_t> > stack_choices;
  std::vector<size_t> visited;
  std::vector<size_t> start;
  start.push_back(0);
  stack_paths.push(start);
  while (!stack_paths.empty()) {
    std::vector<size_t> currentPath = stack_paths.top();
    stack_paths.pop();
    std::vector<size_t> currentChoices;
    if (!stack_choices.empty()) {
      currentChoices = stack_choices.top();
      stack_choices.pop();
    }
    int curPath_len = currentPath.size();
    // get the current page number
    size_t cur_pageNum = currentPath[curPath_len - 1];
    if (pages[cur_pageNum]->getType() == 'W') {
      paths.push_back(currentPath);
      choices.push_back(currentChoices);
      continue;
    }
    if (curPath_len > 1) {
      size_t last_visited = currentPath[curPath_len - 2];
      int visited_len = visited.size();
      while (visited[visited_len - 1] != last_visited) {
        visited.pop_back();
        visited_len = visited.size();
      }
    }
    if (pages[cur_pageNum]->getChoice() != NULL) {
      if (!inVisited(visited, currentPath[curPath_len - 1])) {
        visited.push_back(currentPath[curPath_len - 1]);
        std::vector<size_t> des_pageNums = pages[cur_pageNum]->getDesNums();
        for (size_t i = 0; i < des_pageNums.size(); i++) {
          std::vector<size_t> temp(currentPath);
          temp.push_back(des_pageNums[i]);
          stack_paths.push(temp);
          temp = currentChoices;
          temp.push_back(i + 1);
          stack_choices.push(temp);
        }
      }
    }
  }
}

void printPathsandChoices(std::vector<Page *> & pages) {
  std::vector<std::vector<size_t> > paths;
  std::vector<std::vector<size_t> > choices;
  dfsFindPath(pages, paths, choices);
  if (paths.empty()) {
    std::cout << "This story is unwinnable!" << std::endl;
    return;
  }
  std::stringstream ss;
  for (size_t i = 0; i < paths.size(); i++) {
    std::vector<size_t> curPath = paths[i];
    std::vector<size_t> curChoice = choices[i];
    for (size_t j = 0; j < curChoice.size(); j++) {
      ss << curPath[j] << "(" << curChoice[j] << ")"
         << ",";
    }
    ss << curPath[curPath.size() - 1] << "(win)\n";
  }
  std::cout << ss.str();
}

void chooseStorywthCon(
    std::vector<Page *> & pages,
    std::vector<std::pair<size_t, std::pair<std::string, long int> > > & condition_info) {
  size_t cur_page = 0;
  while (true) {
    std::vector<std::pair<size_t, std::pair<std::string, long int> > >::const_iterator
        it_con = condition_info.begin();
    while (it_con != condition_info.end()) {
      if (cur_page == it_con->first) {
        setConditionForPages(pages, it_con->second.first, it_con->second.second);
      }
      ++it_con;
    }
    std::vector<size_t> unavl_chcNums = pages[cur_page]->printContentandChoicewithCon();
    if (pages[cur_page]->getType() == 'W' || pages[cur_page]->getType() == 'L') {
      break;
    }
    std::vector<size_t> des_pageNums = pages[cur_page]->getDesNums();
    size_t choices_len = pages[cur_page]->getChoicewithConSize();
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
      int found = 0;
      for (size_t i = 0; i < unavl_chcNums.size(); i++) {
        if (choice_num == unavl_chcNums[i]) {
          std::cout << "That choice is not available at this time, please try again"
                    << std::endl;
          found = 1;
          break;
        }
      }
      // if input is unavailable choice, go to the start and get next input
      if (found == 1) {
        continue;
      }
      cur_page = des_pageNums[choice_num - 1];
      validChoice = true;
    }
  }
}

#endif
