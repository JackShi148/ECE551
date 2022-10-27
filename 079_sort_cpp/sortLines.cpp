#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::string line;
    std::vector<std::string> lines;
    while (!std::cin.eof()) {
      std::getline(std::cin, line);
      lines.push_back(line);
    }
    std::sort(lines.begin(), lines.end());
    std::vector<std::string>::iterator it = lines.begin();
    while (it != lines.end()) {
      std::cout << *it << std::endl;
      ++it;
    }
  }
  else if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      std::ifstream ifs(argv[i]);
      if (ifs.fail()) {
        std::cerr << "fail to open file " << argv[i] << std::endl;
        return EXIT_FAILURE;
      }
      std::string line;
      std::vector<std::string> lines;
      while (!ifs.eof()) {
        std::getline(ifs, line);
        lines.push_back(line);
      }
      std::sort(lines.begin(), lines.end());
      std::vector<std::string>::iterator it = lines.begin();
      while (it != lines.end()) {
        std::cout << *it << std::endl;
        ++it;
      }
    }
  }
  return EXIT_SUCCESS;
}
