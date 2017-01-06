#ifndef TREES_H
#define TREES_H

#include <iostream>
#include <stack>

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
  BinaryTree (const char* s, const char* l);
  void preorderBuild (link t, const char* s, const char* l);
  void dump (std::ostream& out, link t, int h) const;
  link getRoot (void);
  friend std::ostream& operator<< (std::ostream& out, const BinaryTree& bt);
  void removeLeaf (Item r);
  friend bool doRemoveLeaf (link t, Item r);
  int countLeaf (link t);
  int countMix (link t);
  bool isLeaf (link t);
  void preorderTraversal (void);
  void inorderTraversal (void);
  void postorderTraversal (void);

  void Tournament (int a[],int l, int r);
  friend link findMax (link t, int a[],int l, int r);
};

#endif
