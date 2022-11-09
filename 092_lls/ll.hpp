#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

class Tester;

class not_exist : public std::exception {
 private:
  const char * message;

 public:
  not_exist() : message("the requested item does not exist") {}
  virtual const char * what() const throw() { return message; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    explicit Node(const T & d) : data(d), next(NULL), prev(NULL) {}
    explicit Node(const T & d, Node * n, Node * p) : data(d), next(n), prev(p){};
  };
  int size;
  Node * head;
  Node * tail;
  bool removeItem(const T & item) {
    bool flag = false;
    Node ** current = &head;
    while (*current != NULL && (*current)->data != item) {
      current = &(*current)->next;
    }
    if ((*current) != NULL && (*current)->data == item) {
      flag = true;
      Node * temp = *current;
      *current = (*current)->next;
      if (*current != NULL) {
        (*current)->prev = temp->prev;
      }
      else {
        tail = temp->prev;
      }
      delete temp;
      size--;
    }
    return flag;
  }

 public:
  LinkedList() : size(0), head(NULL), tail(NULL){};
  LinkedList(const LinkedList & rhs) : size(0), head(NULL), tail(NULL) {
    for (int i = 0; i < rhs.getSize(); i++) {
      addBack(rhs[i]);
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    LinkedList newll;
    for (int i = 0; i < rhs.getSize(); i++) {
      newll.addBack(rhs[i]);
    }
    Node * temp = NULL;
    while (head != NULL) {
      temp = head;
      head = head->next;
      delete temp;
    }
    tail = NULL;
    head = newll.head;
    tail = newll.tail;
    size = rhs.getSize();
    newll.head = NULL;
    newll.tail = NULL;
    return (*this);
  }
  ~LinkedList() {
    Node * temp = NULL;
    while (head != NULL) {
      temp = head;
      head = head->next;
      delete temp;
    }
    head = NULL;
    tail = NULL;
  }
  int getSize() const { return this->size; }
  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (head->next != NULL) {
      head->next->prev = head;
    }
    if (tail == NULL) {
      tail = head;
    }
    size++;
  }
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (tail->prev != NULL) {
      tail->prev->next = tail;
    }
    if (head == NULL) {
      head = tail;
    }
    size++;
  }
  bool remove(const T & item) {
    bool flag = false;
    flag = removeItem(item);
    return flag;
  }
  T & operator[](int index) {
    try {
      if (index < 0 || index >= size) {
        throw(not_exist());
      }
    }
    catch (not_exist & e) {
      std::cerr << e.what() << std::endl;
    }
    Node * cur = head;
    for (int i = 0; i < size; i++) {
      if (i == index) {
        break;
      }
      else {
        cur = cur->next;
      }
    }
    return cur->data;
  }
  const T & operator[](int index) const {
    try {
      if (index < 0 || index >= size) {
        throw(not_exist());
      }
    }
    catch (not_exist & e) {
      std::cerr << e.what() << std::endl;
    }
    Node * cur = head;
    for (int i = 0; i < size; i++) {
      if (i == index) {
        break;
      }
      else {
        cur = cur->next;
      }
    }
    return cur->data;
  }
  int find(const T & item) const {
    int index = -1;
    for (int i = 0; i < size; i++) {
      if (item == (*this)[i]) {
        index = i;
        break;
      }
    }
    return index;
  }
  friend class Tester;
};

#endif
