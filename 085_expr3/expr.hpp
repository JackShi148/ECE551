#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
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
  virtual long evaluate() const {
    long ans = number;
    return ans;
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return ss.str();
  }
  virtual long evaluate() const {
    long ans = 0;
    ans = lhs->evaluate() + rhs->evaluate();
    return ans;
  }
  ~PlusExpression() {
    delete (lhs);
    delete (rhs);
  }
};

class MinusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    return ss.str();
  }
  virtual long evaluate() const {
    long ans = 0;
    ans = lhs->evaluate() - rhs->evaluate();
    return ans;
  }
  ~MinusExpression() {
    delete (lhs);
    delete (rhs);
  }
};

class TimesExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    return ss.str();
  }
  virtual long evaluate() const {
    long ans = 0;
    ans = lhs->evaluate() * rhs->evaluate();
    return ans;
  }
  ~TimesExpression() {
    delete (lhs);
    delete (rhs);
  }
};

class DivExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    return ss.str();
  }
  virtual long evaluate() const {
    long ans = 0;
    ans = lhs->evaluate() / rhs->evaluate();
    return ans;
  }
  ~DivExpression() {
    delete (lhs);
    delete (rhs);
  }
};
