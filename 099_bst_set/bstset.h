#ifndef __BSTSET_H__
#define __BSTSET_H__
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "assert.h"
#include "bstmap.h"
#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  BstMap<T, bool> bstMap;

 public:
  virtual void add(const T & key);
  virtual bool contains(const T & key) const;
  virtual void remove(const T & key);
};
template<typename T>
void BstSet<T>::add(const T & key) {
  bstMap.add(key, true);
}

template<typename T>
bool BstSet<T>::contains(const T & key) const {
  try {
    bstMap.lookup(key);
  }
  catch (const std::invalid_argument & e) {
    return false;
  }
  return true;
}
template<typename T>
void BstSet<T>::remove(const T & key) {
  bstMap.remove(key);
}
#endif
