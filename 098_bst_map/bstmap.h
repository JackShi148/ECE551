#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <cstdlib>
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

    Node(const K & key, const V & value) :
        key(key), value(value), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  virtual void add(const K & key, const V & value) {
    if (root == NULL) {
      root = new Node(key, value);
    }
    else {
      Node * cur = root;
      while (true) {
        if (cur == NULL) {
          cur = new Node(key, value);
          break;
        }
        if (cur->key == key) {
          cur->value = value;
          break;
        }
        else if (cur->key > key) {
          cur = cur->left;
        }
        else {
          cur = cur->right;
        }
      }
    }
  }
  /* virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * ans = findNode(root, key);
    if (ans == NULL) {
      throw std::invalid_argument("not find corresponding key");
    }
    return ans->value;
    }*/
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * target = findNode(this->root, key);
    if (target == NULL) {
      throw std::invalid_argument("key not found");
    }
    else {
      return target->value;
    }
  }
  virtual void remove(const K & key) { root = removeHelper(root, key); }
  Node * removeHelper(Node * cur, const K & key) {
    if (cur == NULL) {
      return cur;
    }
    if (cur->key == key) {
      if (cur->left == NULL) {
        Node * temp = cur->right;
        delete cur;
        return temp;
      }
      else if (cur->right == NULL) {
        Node * temp = cur->left;
        delete cur;
        return temp;
      }
      else {
        K kTarget = findMin(cur->right);
        V vTarget = lookup(kTarget);
        cur->right = removeHelper(cur->right, kTarget);
        cur->key = kTarget;
        cur->value = vTarget;
        return cur;
      }
    }
    else if (cur->key < key) {
      cur->right = removeHelper(cur->right, key);
      return cur;
    }
    else {
      cur->left = removeHelper(cur->left, key);
      return cur;
    }
  }

  /* Node * findNode(Node * cur, const K & key) {
    Node * ans = cur;
    while (ans != NULL) {
      if (ans->key == key) {
        return ans;
      }
      else if (ans->key < key) {
        ans = ans->right;
      }
      else {
        ans = ans->left;
      }
    }
    return ans;
    }*/
  Node * findNode(Node * curr, const K & key) {
    Node * travesal = curr;
    while (travesal != NULL) {
      if (key == travesal->key) {
        return travesal;
      }
      else if (key > travesal->key) {
        travesal = travesal->right;
      }
      else {
        travesal = travesal->left;
      }
    }
    return travesal;
  }

  K findMin(const Node * cur) {
    assert(cur != NULL);
    while (cur->left != NULL) {
      cur = cur->left;
    }
    return cur->key;
  }
  virtual ~BstMap() {}
};

#endif
