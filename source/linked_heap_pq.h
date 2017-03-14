#ifndef LINKED_HEAP_PQ_H
#define LINKED_HEAP_PQ_H

#include <iostream>

template <class Item>
class LinkedHeapPQ {
  struct Node {
    int size;//subtree size
    Item item;
    Node* parent, left, right;
    Node (Item v) {item = v; parent = left = right = size = 0;};
  };
  typedef Node* Link;
  Link root;
  Link lastInserted;
  void FixDown (Link n);
  void FixUp (Link n);
  int getSize (Link n) const;
  void swap (Link a, Link b);
  void restoreLastInserted (void);
  Link insertR (Link n, Item v);
  
  //for debug
  void dumpNode (std::ostream& os, Item v, int h) const  {
    for (int i = 0; i < h; ++i) os << " ";
    os << v << std::endl;
  }
  void dump (std::ostream& os, Link t, int h) const  {
    if (t == 0) {dumpNode(os, '*', h); return;}
    dump (os, t->right, h+1);
    dumpNode(os, t->item, h);
    dump (os, t->left, h+1);
  }

 public:
  typedef Node* Handle;
  LinkedHeapPQ (void)  {root = 0;}
  void change (Handle h, Item v) { h->item = v; FixDown(h); FixUp(h);}
  Handle insert (Item v);
  Item max(void) const {return root->item;}
  //for debug
  friend std::ostream& operator<< (std::ostream& os, const LinkedHeapPQ& rhs)  {
    rhs.dump(os, rhs.root, 0);
    return os;
  }
};

template <class Item>
void LinkedHeapPQ<Item>::swap (Link a, Link b) {

  //handle special case when a is parent of b
  //or b is parent of a
  if (a->left == b) {
    a->left = a;
    b->parent = b;
  }

  if (a->right == b) {
    a->right = a;
    b->parent = b;
  }

  if (b->left == a) {
    b->left = b;
    a->parent = a;
  }

  if (b->right == a) {
    b->right = b;
    a->parent = a;
  }

  //swap a and b
  Node tmp(0);
  tmp.parent = a->parent;
  tmp.left = a->left;
  tmp.right = a->right;

  a->parent = b->parent;
  a->left = b->left;
  a->right = b->right;

  b->parent = tmp.parent;
  b->left = tmp.left;
  b->right = tmp.right;

  //update root if involved
  if (root == a) root = b;
  if (root == b) root = a;
}

template <class Item>
void LinkedHeapPQ<Item>::FixDown (Link n) {
  if (n->left == 0) return;//stop if n is a leaf
  Link max_child = n->left;
  if (n->right && n->right->item > n->left->item) max_child = n->right;
  if (n->item < max_child->item) {//(recursively) degrade n is smaller than its greater child
    swap(n, max_child);
    FixDown(n);
  }
  
}

template <class Item>
void LinkedHeapPQ<Item>::FixUp (Link n) {
  if (n->parent == 0) return;//stop if n is the root
  if (n->parent->item < n->item) {//(recursively) promote n if greater than its parent
    swap(n->parent, n);
    FixUp(n);
  }
}

template <class Item>
int LinkedHeapPQ<Item>::getSize(Link n) const {
  if (n == 0) return 0;
  else return n->size;
}

template <class Item>
typename LinkedHeapPQ<Item>::Link LinkedHeapPQ<Item>::insertR (Link n, Item v) {
  if (n == 0) {
    lastInserted = new Node(v);
    return lastInserted;
  }

  if (getSize(n->right) < getSize(n->left)) {
    Link tmp = insertR(n->right, v);
    n->r = tmp;
    tmp->parent = n;
  }
  else {
    Link tmp = insertR(n->left, v);
    n->l = tmp;
    tmp->parent = n;
  }

  //update size n
  n->size = getSize(n->right) + getSize(n->left) + 1;
  return n;
  
}

template <class Item>
typename LinkedHeapPQ<Item>::Handle  LinkedHeapPQ<Item>::insert (Item v) {
  Handle h;
  if (root == 0){
   root = new Node(v);
   h = lastInserted = root;
  }
  else {
    lastInserted = insertR(root, v);
    FixUp(lastInserted);
    h = lastInserted;
    restoreLastInserted();
  }
  return h;
}

template <class Item>
void  LinkedHeapPQ<Item>::restoreLastInserted (void) {
  if (root == 0) lastInserted = 0;
  Link tmp = root;
  while (tmp->left != 0 && tmp->right != 0) {
    if (getSize(tmp->left) < getSize(tmp->right)) tmp = tmp->right;
    else tmp = tmp->left;
  }
  lastInserted = tmp;//lastInserted is a leaf of the bigger subtree
}

#endif
