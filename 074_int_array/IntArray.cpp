#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
}

IntArray::IntArray(const IntArray & rhs) {
  numElements = rhs.numElements;
  data = new int[numElements];
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    numElements = rhs.numElements;
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    data = temp;
  }
  return *this;
}
const int & IntArray::operator[](int index) const {
}
int & IntArray::operator[](int index) {
}

int IntArray::size() const {
}

bool IntArray::operator==(const IntArray & rhs) const {
}

bool IntArray::operator!=(const IntArray & rhs) const {
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
}
