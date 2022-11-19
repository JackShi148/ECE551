#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

#include "page.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "the number of arguments is wrong!\n";
  }
  std::string dirName(argv[1]);
  std::string storyFile = dirName + "/story.txt";
  std::ifstream ifs(storyFile.c_str(), std::ifstream::in);
  if (!ifs) {
    std::cerr << "fail to open file " << storyFile << std::endl;
    return EXIT_FAILURE;
  }
  std::vector<Page *> pages = parseText(ifs, dirName);
  std::vector<Page *>::const_iterator it = pages.begin();
  while (it != pages.end()) {
    (*it)->printContentandChoice();
    ++it;
  }
  freePages(pages);
  return EXIT_SUCCESS;
}
