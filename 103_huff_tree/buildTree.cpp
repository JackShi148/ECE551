#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  while (pq.size() != 1) {
    Node * cur_node_1 = pq.top();
    pq.pop();
    Node * cur_node_2 = pq.top();
    pq.pop();
    pq.push(new Node(cur_node_1, cur_node_2));
  }
  Node * root = pq.top();
  pq.pop();
  return root;
}
