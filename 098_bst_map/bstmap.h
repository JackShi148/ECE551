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
  /*BstMap() : root(NULL) {}
  virtual void add(const K & key, const V & value) {
    this->root = addHelper(this->root, key, value);
  }
  Node * addHelper(Node * cur, const K & key, const V & value) {
    if (cur == NULL) {
      cur = new Node(key, value);
      return cur;
    }
    else {
      if (cur->key == key) {
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
      if (cur->key == key) {
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
      throw std::invalid_argument("not find corresponding key");
    }
    return cur->value;
  }
  virtual void remove(const K & key) {
    Node ** cur = &root;
    while (*cur != NULL) {
      if ((*cur)->key == key) {
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
      throw std::invalid_argument("not find corresponding key");
    }
    if ((*cur)->left == NULL) {
      Node * temp = (*cur)->right;
      delete *cur;
      *cur = temp;
    }
    else if ((*cur)->right == NULL) {
      Node * temp = (*cur)->left;
      delete *cur;
      *cur = temp;
    }
    else {
      Node * closestLargestNode = (*cur)->right;
      while (closestLargestNode->left != NULL) {
        closestLargestNode = closestLargestNode->left;
      }
      K Ktemp = closestLargestNode->key;
      V Vtemp = closestLargestNode->value;
      remove(closestLargestNode->key);
      (*cur)->key = Ktemp;
      (*cur)->value = Vtemp;
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

  virtual ~BstMap() { destroy(this->root); }*/
  BstMap() : root(NULL) {}
  ~BstMap() { destroy(root); }
  //destroy helper function
  void destroy(Node * current) {
    if (current == NULL) {
      return;
    }
    destroy(current->left);
    destroy(current->right);
    delete current;
  }

  //add
  void add(const K & key, const V & value) { root = addnode(root, key, value); }
  //add helper function
  Node * addnode(Node * current, const K & key, const V & value) {
    if (current == NULL) {
      Node * ans = new Node(key, value);
      return ans;
    }
    else {
      if (key == current->key) {
        current->value = value;
        return current;
      }
      else if (key < current->key) {
        current->left = addnode(current->left, key, value);
      }
      else {
        current->right = addnode(current->right, key, value);
      }
      return current;
    }
  }

  //lookup
  const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        break;
        //return current->value;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }

    if (current == NULL) {
      throw std::invalid_argument("key not find\n");
    }
    return current->value;
  }

  //remove
  void remove(const K & key) {
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
      //return;
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
      //Node * similarnode = similar((*current)->left);
      K tempkey = findnode->key;
      V tempvalue = findnode->value;
      remove(findnode->key);
      (*current)->key = tempkey;
      (*current)->value = tempvalue;
    }
  }
};

#endif
