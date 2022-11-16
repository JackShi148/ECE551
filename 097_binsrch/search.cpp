#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high || low == high - 1) {
    return low;
  }
  int mid = (high - low) / 2 + low;
  int val = f->invoke(mid);
  int ans = low;
  if (val == 0) {
    ans = mid;
    return ans;
  }
  else if (val < 0) {
    //cannot let mid plus 1, because it may cause boundary problem
    ans = binarySearchForZero(f, mid, high);
  }
  else {
    //same problem if high = mid - 1
    ans = binarySearchForZero(f, low, mid);
  }
  return ans;
}
