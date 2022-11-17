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
  BstMap(const BstMap & rhs) { root = copyHelper(rhs.root); }
  Node * copyHelper(Node * cur) {
    if (cur == NULL) {
      return NULL;
    }
    Node * ans = new Node(cur->key, cur->value);
    ans->left = copyHelper(ans->left);
    ans->right = copyHelper(ans->right);
    return ans;
  }
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      BstMap<K, V> temp(rhs);
      std::swap(root, temp.root);
    }
    return *this;
  }
  virtual void add(const K & key, const V & value) {
    this->root = addHelper(this->root, key, value);
  }
  Node * addHelper(Node * cur, const K & key, const V & value) {
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

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
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
  virtual void remove(const K & key) {
    Node ** current = &root;
    while (*current != NULL) {
      if (key == (*current)->key) {
        break;
      }
      else if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else {
        current = &(*current)->right;
      }
    }
    if (*current == NULL) {
      throw std::invalid_argument("key not find\n");
    }
    if ((*current)->left == NULL) {
      Node * temp = (*current)->right;
      delete (*current);
      *current = temp;
    }
    else if ((*current)->right == NULL) {
      Node * temp = (*current)->left;
      delete (*current);
      *current = temp;
    }
    else {
      Node * findnode = (*current)->left;
      while (findnode->right != NULL) {
        findnode = findnode->right;
      }

      K tempkey = findnode->key;
      V tempvalue = findnode->value;
      remove(findnode->key);
      (*current)->key = tempkey;
      (*current)->value = tempvalue;
    }
  }
  void destroy(Node * cur) {
    if (cur == NULL) {
      return;
    }
    destroy(cur->left);
    destroy(cur->right);
    delete cur;
  }

  virtual ~BstMap() { destroy(root); }
};

#endif
