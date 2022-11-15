#include <cmath>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int remaining = 0;
  if (low < high) {
    remaining = log2(high - low) + 1;
  }
  else {
    remaining = 1;
  }
  CountedIntFn * fn = new CountedIntFn(remaining, f, mesg);
  //do binary search
  int val = binarySearchForZero(fn, low, high);
  //check if answer is right
  if (val != expected_ans) {
    fprintf(stderr, "The answer of %s is wrong", mesg);
    exit(EXIT_FAILURE);
  }
}
// sin
class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};
// constant 10
class PosFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10; }
};
// constant -10
class NegFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -10; }
};
// monotonically increasing function: f(x) = x + 5
class MiFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg + 5; }
};
// monotonically decreasing function: f(x) = -x + 1
class MdFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -arg + 1; }
};

int main() {
  SinFunction sf;
  PosFunction pf;
  NegFunction nf;
  MiFunction mif;
  MdFunction mdf;
  // check sin
  check(&sf, 0, 150000, 52359, "SinFunction in range[0, 150000)");

  //check constant 10
  check(&pf, -10, 10, -10, "PosFunciton in range[-10, 10)");
  check(&pf, -100, -10, -100, "PosFunciton in range[-100, -10)");
  check(&pf, 10, 100, 10, "PosFunciton in range[10, 100)");
  check(&pf, 0, 0, 0, "PosFunciton in (0, 0)");

  //check constant -10
  check(&nf, -10, 10, 9, "NegFunction in range[-10, 10)");
  check(&nf, -100, -10, -11, "NegFunction in range[-100, -10)");
  check(&nf, 10, 100, 99, "NegFunction in range[10, 100)");
  check(&nf, 0, 0, 0, "NegFunction in (0, 0)");

  //check x + 5
  check(&mif, -10, 10, -5, "MiFunction in range[-10, 10)");
  check(&mif, -100, -10, -11, "MiFunction in range[-100, -10)");
  check(&mif, 10, 100, 10, "MiFunction in range[10, 100)");
  check(&mif, 0, 0, 0, "MiFunction in (0, 0)");

  //check -x + 1
  check(&mdf, -100, 100, 1, "MdFunction in range[-100, 100)");
  check(&mdf, -100, -10, -100, "MdFunction in range[-100, -10)");
  check(&mdf, 10, 100, 99, "MdFunction in range[10, 100)");
  check(&mdf, 0, 0, 0, "MdFunction in (0, 0)");

  return EXIT_SUCCESS;
}
