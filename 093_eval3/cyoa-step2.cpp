#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "page.hpp"
#include "story.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "the number of arguments is wrong\n" << std::endl;
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

  chooseStory(pages);

  freePages(pages);
  ifs.close();
  return EXIT_SUCCESS;
}
