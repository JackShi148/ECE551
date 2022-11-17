#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "assert.h"
#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL) {}
    Node(const K & key, const V & value) :
        key(key), value(value), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs);
  BstMap & operator=(const BstMap & rhs);
  virtual ~BstMap();
  virtual void add(const K & key, const V & value);
  virtual const V & lookup(const K & key) const throw(std::invalid_argument);
  virtual void remove(const K & key);
  Node * copyHelper(Node * current);
  Node * addHelper(Node * current, const K & key, const V & value);
  void destroy(Node * current);
};
template<typename K, typename V>
BstMap<K, V>::BstMap(const BstMap & rhs) {
  root = copyHelper(rhs.root);
}
template<typename K, typename V>
typename BstMap<K, V>::Node * BstMap<K, V>::copyHelper(Node * cur) {
  if (cur == NULL) {
    return NULL;
  }
  Node * mynode = new Node(cur->key, cur->value);
  mynode->left = copyHelper(cur->left);
  mynode->right = copyHelper(cur->right);
  return mynode;
}
template<typename K, typename V>
BstMap<K, V> & BstMap<K, V>::operator=(const BstMap & rhs) {
  if (this != &rhs) {
    BstMap<K, V> temp(rhs);
    std::swap(root, temp.root);
  }
  return *this;
}
template<typename K, typename V>
void BstMap<K, V>::add(const K & key, const V & value) {
  this->root = addHelper(this->root, key, value);
}
template<typename K, typename V>
typename BstMap<K, V>::Node * BstMap<K, V>::addHelper(Node * cur,
                                                      const K & key,
                                                      const V & value) {
  if (cur == NULL) {
    Node * ans = new Node(key, value);
    return ans;
  }
  else {
    if (key == cur->key) {
      cur->value = value;
      return cur;
    }
    else if (key < cur->key) {
      cur->left = addHelper(cur->left, key, value);
    }
    else {
      cur->right = addHelper(cur->right, key, value);
    }
    return cur;
  }
}
template<typename K, typename V>
const V & BstMap<K, V>::lookup(const K & key) const throw(std::invalid_argument) {
  Node * cur = root;
  while (cur != NULL) {
    if (key == cur->key) {
      break;
    }
    else if (key < cur->key) {
      cur = cur->left;
    }
    else {
      cur = cur->right;
    }
  }

  if (cur == NULL) {
    throw std::invalid_argument("key not find\n");
  }
  return cur->value;
}
template<typename K, typename V>
void BstMap<K, V>::remove(const K & key) {
  Node ** cur = &root;
  while (*cur != NULL) {
    if (key == (*cur)->key) {
      break;
    }
    else if (key < (*cur)->key) {
      cur = &(*cur)->left;
    }
    else {
      cur = &(*cur)->right;
    }
  }
  if (*cur == NULL) {
    throw std::invalid_argument("key not find\n");
  }
  if ((*cur)->left == NULL) {
    Node * temp = (*cur)->right;
    delete (*cur);
    *cur = temp;
  }
  else if ((*cur)->right == NULL) {
    Node * temp = (*cur)->left;
    delete (*cur);
    *cur = temp;
  }
  else {
    Node * closestLargest = (*cur)->left;
    while (closestLargest->right != NULL) {
      closestLargest = closestLargest->right;
    }

    K tempkey = closestLargest->key;
    V tempvalue = closestLargest->value;
    remove(closestLargest->key);
    (*cur)->key = tempkey;
    (*cur)->value = tempvalue;
  }
}
template<typename K, typename V>
BstMap<K, V>::~BstMap() {
  destroy(root);
}
template<typename K, typename V>
void BstMap<K, V>::destroy(Node * cur) {
  if (cur == NULL) {
    return;
  }
  destroy(cur->left);
  destroy(cur->right);
  delete cur;
}

#endif
