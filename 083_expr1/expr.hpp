#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long number;

 public:
  NumExpression(long n) : number(n) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << number;
    return ss.str();
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * E1;
  Expression * E2;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : E1(lhs), E2(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << E1->toString() << " + " << E2->toString() << ")";
    return ss.str();
  }
  ~PlusExpression() {
    delete (E1);
    delete (E2);
  }
};
