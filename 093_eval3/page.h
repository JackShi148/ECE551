#ifndef __PAGE_H__
#define __PAGE_H__
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
class Page {
 private:
  class Choice {
   public:
    size_t src_pageNum;
    std::vector<size_t> des_pageNums;
    std::vector<std::string> choices;
    void addChoice(const size_t & des_pageNum, const std::string & choice) {
      des_pageNums.push_back(des_pageNum);
      choices.push_back(choice);
    }
    Choice(size_t src_pageNum, const size_t & des_pageNum, const std::string & choice) :
        src_pageNum(src_pageNum) {
      des_pageNums.push_back(des_pageNum);
      choices.push_back(choice);
    }
    Choice(size_t src_pageNum,
           const std::vector<size_t> & des_pageNums,
           const std::vector<std::string> & choices) :
        src_pageNum(src_pageNum), des_pageNums(des_pageNums), choices(choices) {}
  };
  Choice * choice;
  size_t page_num;
  char type;
  std::string page_name;
  std::vector<std::string> content;

 public:
  Page() : choice(NULL), page_num(0), type('N') {}
  Page(size_t page_num, char type, std::string page_name) :
      choice(NULL), page_num(page_num), type(type), page_name(page_name) {}
  Page(const Page & rhs);
  Page & operator=(const Page & rhs);
  void printContentandChoice() const;
  ~Page();
  friend std::vector<Page *> parseText(std::ifstream & ifs, std::string dirName);
};

//copy constructor
Page::Page(const Page & rhs) :
    choice(NULL),
    page_num(rhs.page_num),
    type(rhs.type),
    page_name(rhs.page_name),
    content(rhs.content) {
  choice =
      new Choice(rhs.choice->src_pageNum, rhs.choice->des_pageNums, rhs.choice->choices);
}
//assignment constructor
Page & Page::operator=(const Page & rhs) {
  if (this != &rhs) {
    Choice * temp = new Choice(
        rhs.choice->src_pageNum, rhs.choice->des_pageNums, rhs.choice->choices);
    delete choice;
    choice = temp;
    content = rhs.content;
    page_num = rhs.page_num;
    type = rhs.type;
    page_name = rhs.page_name;
  }
  return *this;
}

//print the content and choices of every page
void Page::printContentandChoice() const {
  std::stringstream ss;
  ss << "Page " << page_num << '\n';
  ss << "==========\n";
  std::vector<std::string>::const_iterator it_cnt = content.begin();
  while (it_cnt != content.end()) {
    ss << *it_cnt << '\n';
    ++it_cnt;
  }
  //ss << '\n';
  if (type == 'W') {
    ss << "Congratulations! You have won. Hooray!\n";
  }
  else if (type == 'L') {
    ss << "Sorry, you have lost. Better luck next time!\n";
  }
  else if (type == 'N') {
    ss << "What would you like to do?\n\n";
    std::vector<std::string>::const_iterator it_chs = choice->choices.begin();
    int i = 1;
    while (it_chs != choice->choices.end()) {
      ss << ' ' << i << ". " << *it_chs << '\n';
      ++i;
      ++it_chs;
    }
  }
  std::cout << ss.str();
}
Page::~Page() {
  delete choice;
}
std::vector<Page *> parseText(std::ifstream & ifs, std::string dirName) {
  std::vector<Page *> pages;
  std::string line;
  while (!ifs.eof()) {
    std::getline(ifs, line);
    if (!line.empty()) {
      // page declaration
      if (line.find('@') != std::string::npos) {
        size_t at_pos = line.find('@');
        size_t page_num = strtoul(line.c_str(), NULL, 10);
        char type = line[at_pos + 1];
        size_t colon = line.find(':');
        std::string page_name = line.substr(colon + 1);
        Page * new_page = new Page(page_num, type, page_name);
        pages.push_back(new_page);
        std::string page_addr = dirName + '/' + page_name;
        std::ifstream page_ifs(page_addr.c_str(), std::ifstream::in);
        std::string content_line;
        while (!page_ifs.eof()) {
          std::getline(page_ifs, content_line);
          new_page->content.push_back(content_line);
        }
      }
      // choices declaration
      else {
        size_t first_colon = line.find(':');
        size_t second_colon = line.find(':', first_colon + 1);
        std::string des = line.substr(first_colon + 1, second_colon - first_colon - 1);
        size_t src_pageNum = strtoul(line.c_str(), NULL, 10);
        size_t des_pageNum = strtoul(des.c_str(), NULL, 10);
        std::string choice = line.substr(second_colon + 1);
        if (pages[src_pageNum]->choice == NULL) {
          pages[src_pageNum]->choice = new Page::Choice(src_pageNum, des_pageNum, choice);
        }
        else {
          pages[src_pageNum]->choice->addChoice(des_pageNum, choice);
        }
      }
    }
  }
  return pages;
}

void freePages(std::vector<Page *> & pages) {
  int len = pages.size();
  for (int i = 0; i < len; i++) {
    delete pages[i];
  }
}

#endif
