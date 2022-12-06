#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

#include "page.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "the number of arguments is wrong!\n";
    return EXIT_FAILURE;
  }
  std::string dirName(argv[1]);
  std::string storyFile = dirName + "/story.txt";
  std::ifstream ifs(storyFile.c_str(), std::ifstream::in);
  if (!ifs) {
    std::cerr << "fail to open file " << storyFile << std::endl;
    return EXIT_FAILURE;
  }
  std::vector<Page *> pages = parseText(ifs, dirName);
  check(pages);
  std::vector<Page *>::iterator it = pages.begin();
  while (it != pages.end()) {
    std::cout << "Page " << (*it)->getPageNum() << std::endl;
    std::cout << "==========" << std::endl;
    (*it)->printContentandChoice();
    ++it;
  }
  freePages(pages);
  ifs.close();
  return EXIT_SUCCESS;
}
