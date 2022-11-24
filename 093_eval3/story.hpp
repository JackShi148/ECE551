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

bool inVisited(std::vector<char> & visited, char target) {
  int len = visited.size();
  for (int i = 0; i < len; i++) {
    if (visited[i] == target) {
      return true;
    }
  }
  return false;
}

void dfsFindPath(std::vector<Page *> & pages,
                 std::vector<std::string> & paths,
                 std::vector<std::string> & choices) {
  std::stack<std::string> stack_paths;
  std::stack<std::string> stack_choices;
  std::vector<char> visited;
  stack_paths.push("0");
  while (!stack_paths.empty()) {
    std::string currentPath = stack_paths.top();
    stack_paths.pop();
    std::string currentChoices = stack_choices.top();
    stack_choices.pop();
    int curPath_len = currentPath.size();
    // get the current page number
    int cur_pageNum = currentPath[curPath_len - 1] - '0';
    if (pages[cur_pageNum]->getType() == 'W') {
      paths.push_back(currentPath);
      choices.push_back(currentChoices);
      continue;
    }
    if (curPath_len > 1) {
      char second_char = currentPath[curPath_len - 2];
      int visited_len = visited.size();
      while (visited[visited_len - 1] != second_char) {
        visited.pop_back();
        visited_len = visited.size();
      }
    }
    if (pages[cur_pageNum]->getChoice() != NULL) {
      if (!inVisited(visited, currentPath[curPath_len - 1])) {
        visited.push_back(currentPath[curPath_len - 1]);
        std::vector<size_t> des_pageNums = pages[cur_pageNum]->getDesNums();
        for (size_t i = 0; i < des_pageNums.size(); i++) {
          std::stringstream ss;
          ss << des_pageNums[i];
          std::string temp = ss.str();
          currentPath += temp;
          stack_paths.push(currentPath);
          ss.str("");
          ss << i + 1;
          temp = ss.str();
          currentChoices += temp;
          stack_choices.push(currentChoices);
        }
      }
    }
  }
}

void printPathsandChoices(std::vector<Page *> & pages) {
  std::vector<std::string> paths;
  std::vector<std::string> choices;
  dfsFindPath(pages, paths, choices);
  if (paths.empty()) {
    std::cout << "This story is unwinnable!" << std::endl;
    return;
  }
  std::stringstream ss;
  for (size_t i = 0; i < paths.size(); i++) {
    std::string curPath = paths[i];
    std::string curChoice = choices[i];
    for (size_t j = 0; j < curChoice.size(); j++) {
      ss << curPath[j] << "(" << curChoice[j] << ")"
         << ",";
    }
    ss << curPath[curPath.size() - 1] << "(win)\n";
  }
  std::cout << ss.str();
}

#endif
