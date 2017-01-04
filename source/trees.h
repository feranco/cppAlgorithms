#ifndef TREES_H
#define TREES_H

#include <iostream>

typedef int Item;

class BinaryTree {
  struct Node {
    Item item;
    Node* l;
    Node* r;
    Node (Item x) {item = x; l = r = 0;}
  };
  typedef Node* link;
  link root;
 public:
  BinaryTree () {root = 0;};
  void dump (std::ostream& out, link t, int h) const;
  void Tournament (int a[],int l, int r);
  friend link findMax (link t, int a[],int l, int r);
  friend std::ostream& operator<< (std::ostream& out, const BinaryTree& bt);
  void removeLeaf (Item r);
  friend bool doRemoveLeaf (link t, Item r);
  int countLeaf (void);
  int subTreeLeaf (link t);
  int countMix (void);
  int subTreeMix (link t);
  bool isLeaf (link t);
  int intPathLength (
};

#endif
