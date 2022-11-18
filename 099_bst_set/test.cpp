#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "bstmap.h"
#include "bstset.h"
#include "map.h"
#include "set.h"

int main(void) {
  BstSet<int> set;
  try {
    set.add(60);
    set.add(19);
    set.add(93);
    set.add(4);
    set.add(25);
    set.add(84);
    set.add(1);
    set.add(11);
    set.add(21);
    set.add(35);
    set.add(70);
    set.add(86);

    std::cout << "Lookup key is: " << 25 << " value is: " << set.contains(25)
              << std::endl;
    std::cout << "Lookup key is: " << 60 << " value is: " << set.contains(60)
              << std::endl;

    //map.remove(8);
    //map.remove(19);
    // map.remove(19);
    //map.remove(70);
    set.remove(86);

    //map.printing();
    std::cout << "Lookup key is:" << 86 << " value is: " << set.contains(86) << std::endl;
  }
  catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}
