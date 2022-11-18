#ifndef __PAGE_H__
#define __PAGE_H__
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Page {
 private:
  class Choice {
   public:
    size_t src_pageNum;
    std::vector<size_t> des_pageNum;
    std::vector<std::string> choices;
    Choice(size_t src_pageNum,
           const std::vector<size_t> & des_pageNum,
           const std::vector<std::string> & choices) :
        src_pageNum(src_pageNum), des_pageNum(des_pageNum), choices(choices) {}
  };
  Choice * Choices;
  size_t page_num;
  char type;
  std::string page_name;
  std::vector<std::string> content;

 public:
  Page() : Choices(NULL), page_num(0), type('N') {}
  Page(const Page & rhs);
  Page & operator=(const Page & rhs);
  void parseText(std::ifstream & ifs);
  void printContentandChoice();
  ~Page();
};

void Page::parseText(std::ifstream & ifs) {
}
//copy constructor
Page::Page(const Page & rhs) :
    Choices(NULL),
    page_num(rhs.page_num),
    type(rhs.type),
    page_name(rhs.page_name),
    content(rhs.content) {
  Choices = new Choice(
      rhs.Choices->src_pageNum, rhs.Choices->des_pageNum, rhs.Choices->choices);
}
//assignment constructor
Page & Page::operator=(const Page & rhs) {
  if (this != &rhs) {
    Choice * temp = new Choice(
        rhs.Choices->src_pageNum, rhs.Choices->des_pageNum, rhs.Choices->choices);
    delete Choices;
    content.clear();
    Choices = temp;
    content = rhs.content;
    page_num = rhs.page_num;
    type = rhs.type;
    page_name = rhs.page_name;
  }
  return *this;
}

//print the content and choices of every page
void Page::printContentandChoice() {
  std::stringstream ss;
  ss << "Page " << page_num << '\n';
  ss << "==========\n";
  std::vector<std::string>::const_iterator it_cnt = content.begin();
  while (it_cnt != content.end()) {
    ss << *it_cnt << '\n';
    ++it_cnt;
  }
  ss << '\n';
  if (type == 'W') {
    ss << "Congratulations! You have won. Hooray!\n";
  }
  else if (type == 'L') {
    ss << "Sorry, you have lost. Better luck next time!\n";
  }
  else if (type == 'N') {
    ss << "Waht would you like to do?\n\n";
    std::vector<std::string>::const_iterator it_chs = Choices->choices.begin();
    int i = 1;
    while (it_chs != Choices->choices.end()) {
      ss << ' ' << i << ". " << *it_chs << '\n';
      ++i;
      ++it_chs;
    }
  }
  std::cout << ss.str();
}

#endif
