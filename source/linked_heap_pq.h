#ifndef LINKED_HEAP_PQ_H
#define LINKED_HEAP_PQ_H

#include <iostream>

template <class Item>
class LinkedHeapPQ {

  struct Node {
    int size;//subtree size
    Item item;
    Node* parent, *left, *right;
    Node(Item v) { item = v; parent = left = right = 0; size = 1; };
    };
  typedef Node* Link;

  Link root;
  Link lastInserted;
  void FixDown(Link n);
  void FixUp(Link n);
  int getSize(Link n) const;
  void swapLinked(Link a, Link b);
  void swapGeneric(Link a, Link b);
  void swap(Link a, Link b);
  void restoreLastInserted(void);
  Link insertR(Link n, Item v);
  int maxHeight(Link p);


  //for debug
  void dumpIntNode(std::ostream& os, Item v, int h) const;
  void dumpExtNode(std::ostream& os, int h) const; 
  void dump(std::ostream& os, Link t, int h) const;
 
 public:
  typedef Node* Handle;
  LinkedHeapPQ(void) { root = 0; }
  void change(Handle h, Item v) { h->item = v; FixDown(h); FixUp(h); }
  void remove(Handle n);
  Handle insert(Item v);
  Item max(void) const { return root->item; }
  //for debug
  friend std::ostream& operator<< (std::ostream& os, const LinkedHeapPQ& rhs) {
    rhs.dump(os, rhs.root, 0);
    return os;
  }

};

template <class Item>
void LinkedHeapPQ<Item>::dumpIntNode(std::ostream& os, Item v, int h) const {
  for (int i = 0; i < h; ++i) os << "  ";
  os << v << std::endl;
}

template <class Item>
void LinkedHeapPQ<Item>::dumpExtNode(std::ostream& os, int h) const {
  for (int i = 0; i < h; ++i) os << "  ";
  os << '*' << std::endl;
}

template <class Item>
void LinkedHeapPQ<Item>::dump(std::ostream& os, Link t, int h) const {
  if (t == 0) { dumpLeaf(os, h); return; }

  dump(os, t->right, h + 3);
  dumpNode(os, t->item, h);
  dump(os, t->left, h + 3);
}

//special case wher p is the parent of c
template <class Item>
void LinkedHeapPQ<Item>::swapLinked(Link p, Link c) {

  //update p child in order to point p
  if (p->left == c) p->left = p;
  else p->right = p;
  //update c parent in order to point c
  c->parent = c;
  //update p parent in order to point c
  if (p->parent && p->parent->left == p) p->parent->left = c;
  if (p->parent && p->parent->right == p) p->parent->right = c;
  //update c child in order to point p
  if (c->left) c->left->parent = p;
  if (c->right) c->right->parent = p;

  //swap p and c
  Node tmp(0);
  tmp.parent = p->parent;
  tmp.left = p->left;
  tmp.right = p->right;
  tmp.size = p->size;

  p->parent = c->parent;
  p->left = c->left;
  p->right = c->right;
  p->size = c->size;

  c->parent = tmp.parent;
  c->left = tmp.left;
  c->right = tmp.right;
  c->size = tmp.size;

  //update root if involved
  if (root == p) root = c;
}

template <class Item>
void LinkedHeapPQ<Item>::swap(Link a, Link b) {
  if (a->left == b || a->right == b) swapLinked(a, b);
  else if (b->left == a || b->right == a) swapLinked(b, a);
  else swapGeneric(a, b);
}


template <class Item>
void LinkedHeapPQ<Item>::swapGeneric(Link a, Link b) {

  //swap a and b
  Node tmp(0);
  tmp.parent = a->parent;
  tmp.left = a->left;
  tmp.right = a->right;
  tmp.size = a->size;

  a->parent = b->parent;
  a->left = b->left;
  a->right = b->right;
  a->size = b->size;

  b->parent = tmp.parent;
  b->left = tmp.left;
  b->right = tmp.right;
  b->size = tmp.size;

  //update a parent in order to point b
  if (a->parent) {
    if (a->parent->left == a) a->parent->left = b;
    else a->parent->right = b;
  }

  //update b parent in order to point a
  if (b->parent) {
    if (b->parent->left == b) b->parent->left = a;
    else b->parent->right = a;
  }

  //update a childs in order to point b
  if (a->left) a->left->parent = b;
  if (a->right) a->right->parent = b;

  //update b childs in order to point a
  if (b->left) b->left->parent = a;
  if (b->right) b->right->parent = a;

  //update root if involved
  if (root == a) root = b;
  else if (root == b) root = a;
}

template <class Item>
void LinkedHeapPQ<Item>::FixDown(Link n) {
  if (n->left == 0) return;//stop if n is a leaf
  Link max_child = n->left;
  if (n->right && n->right->item > n->left->item) max_child = n->right;
  if (n->item < max_child->item) {//(recursively) degrade n is smaller than its greater child
    swap(n, max_child);
    FixDown(n);
  }

}

template <class Item>
void LinkedHeapPQ<Item>::FixUp(Link n) {
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

//to be fixed
template <class Item>
void LinkedHeapPQ<Item>::remove(Handle h) {
  std::cout << "rem " <<h->item << std::endl;
  //swap h with the lastInserted node
  swap(h, lastInserted);

  if (h->parent->left == h) h->parent->left = 0;
  else h->parent->right = 0;

  delete h;

  FixDown(lastInserted);
  restoreLastInserted();

}


template <class Item>
typename LinkedHeapPQ<Item>::Link LinkedHeapPQ<Item>::insertR(Link n, Item v) {
  if (n == 0) {
    lastInserted = new Node(v);
    return lastInserted;
  }

  if (getSize(n->right) < getSize(n->left)) {
    Link tmp = insertR(n->right, v);
    n->right = tmp;
    tmp->parent = n;
  }
  else {
    Link tmp = insertR(n->left, v);
    n->left = tmp;
    tmp->parent = n;
  }

  //update size n
  n->size = getSize(n->right) + getSize(n->left) + 1;
  return n;

}

template <class Item>
typename LinkedHeapPQ<Item>::Handle LinkedHeapPQ<Item>::insert(Item v) {
  Handle h;
  if (root == 0) {
    root = new Node(v);
    h = lastInserted = root;
  }
  else {
    //lastInserted = insertR(root, v);
    insertR(root, v);
    FixUp(lastInserted);
    h = lastInserted;
    restoreLastInserted();
  }
  return h;
}

template <class Item>
void  LinkedHeapPQ<Item>::restoreLastInserted(void) {
  if (root == 0) lastInserted = 0;
  Link tmp = root;
  while (tmp->left != 0 || tmp->right != 0) {
    if (getSize(tmp->left) < getSize(tmp->right)) tmp = tmp->right;
    else tmp = tmp->left;
  }
  lastInserted = tmp;//lastInserted is a leaf of the bigger subtree
}

#include <iostream>
#include <fstream>
void testLinkedHeap(void) {
  std::ofstream fout("tree_pretty.txt");
  LinkedHeapPQ<int> pq;
  LinkedHeapPQ<int>::Handle handle[12];
  for (int i = 0; i < 12; ++i) handle[i] = pq.insert((rand() % 999) + 1);
  std::cout << pq;
  fout << pq;
  //pq.change(handle[2], 21);
  //std::cout << "------------" << endl;
  //std::cout << pq;
  std::cout << "------------" << std:endl;
  pq.remove(handle[4]);
  std::cout << pq;
}
#endif
