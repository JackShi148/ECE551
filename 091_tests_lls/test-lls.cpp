#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAdd() {
    IntList il;
    il.addFront(1);  //[1]
    assert(il.getSize() == 1 && il.head != NULL && il.tail == il.head &&
           il.head->data == 1 && il.head->next == NULL && il.head->prev == NULL);
    il.addFront(2);  //[2,1]
    assert(il.getSize() == 2 && il.head != NULL && il.head->next != NULL &&
           il.tail == il.head->next && il.head->data == 2 && il.head->prev == NULL &&
           il.head->next->prev == il.head && il.head->next->next == NULL);
    il.addBack(3);  //[2,1,3]
    assert(il.getSize() == 3 && il.head->data == 2 && il.head->next->next->data == 3 &&
           il.head->next->data == 1 && il.tail->data == 3 && il.tail->next == NULL &&
           il.head->next == il.tail->prev && il.tail->prev->prev == il.head);
  }
  void testRuleofThree() {
    IntList list1;
    list1.addFront(1);
    list1.addBack(2);  //[1,2]
    IntList list2(list1);
    assert(list2.getSize() == 2 && list2.head->data == 1 && list2.head->next->data == 2 &&
           list2.head->next == list2.tail && list2.tail->prev == list2.head &&
           list2.head->prev == NULL && list2.head->prev == list2.tail->next);
    list1.remove(2);  //[1]
    list2 = list1;    //[1]
    assert(list2.getSize() == 1 && list2.head->data == 1 && list2.head == list2.tail &&
           list2.head->next == NULL && list2.head->next == list2.head->prev);
  }
  void testRemoval() {
    IntList il;
    il.addFront(1);
    il.addBack(2);  //[1,2]
    bool flag = false;
    flag = il.remove(2);  //[1]
    assert(flag == true && il.getSize() == 1 && il.head->data == 1 &&
           il.tail == il.head && il.head->next == NULL && il.head->next == il.head->prev);
    flag = false;
    il.addFront(2);       //[2,1]
    flag = il.remove(2);  //[1]
    assert(flag == true && il.getSize() == 1 && il.head->data == 1 &&
           il.head == il.tail && il.head->next == NULL && il.head->next == il.head->prev);
    flag = il.remove(2);  //[1]
    assert(flag == false && il.getSize() == 1 && il.head->data == 1 &&
           il.head == il.tail && il.head->next == NULL && il.head->next == il.head->prev);
    il.addFront(1);       //[1,1]
    flag = il.remove(1);  //[1]
    assert(flag == true && il.getSize() == 1 && il.head->data == 1 &&
           il.head == il.tail && il.head->next == NULL && il.head->next == il.tail->prev);
    flag = il.remove(1);  //[]
    assert(flag == true && il.getSize() == 0 && il.head == NULL && il.head == il.tail);
    il.addFront(1);
    il.addFront(3);
    il.addFront(2);       //[2,3,1]
    flag = il.remove(3);  //[2,1]
    assert(flag == true && il.getSize() == 2 && il.head->data == 2 &&
           il.tail->data == 1 && il.head->next == il.tail && il.tail->prev == il.head &&
           il.head->prev == NULL && il.head->prev == il.tail->next);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAdd();
  t.testRemoval();
  t.testRuleofThree();
  return EXIT_SUCCESS;
}
