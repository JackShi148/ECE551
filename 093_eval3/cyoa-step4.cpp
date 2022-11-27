#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "page.hpp"
#include "story.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "the number of arguments is wrong" << std::endl;
    return EXIT_FAILURE;
  }
  std::vector<std::pair<size_t, std::pair<std::string, long int> > > condition_info;
  std::string dirName(argv[1]);
  std::string storyFile = dirName + "/story.txt";
  std::ifstream ifs(storyFile.c_str(), std::ifstream::in);
  if (!ifs) {
    std::cerr << "fail to open file " << storyFile << std::endl;
    return EXIT_FAILURE;
  }
  std::vector<Page *> pages = parseTextwithCons(ifs, dirName, condition_info);
  check(pages);
  chooseStorywthCon(pages, condition_info);
  freePages(pages);
  ifs.close();
  return EXIT_SUCCESS;
}
