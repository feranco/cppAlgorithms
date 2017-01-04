#include "trees.h"

void BinaryTree::Tournament (int a[],int l, int r) {
  root = findMax (root, a, l, r);
}

BinaryTree::link findMax (BinaryTree::link t, int a[],int l,int r) {

  int m = (l + r) / 2;
  t = new  BinaryTree::Node (a[m]);
  if (l == r) return t;
  t->l  = findMax (t->l, a, l, m);
  t->r = findMax (t->r, a, m+1, r);

  if (t->l->item > t->r->item) {
    t->item = t->l->item;
  }
  else {
    t->item = t->r->item;
  }
  return t;

}

std::ostream& operator<< (std::ostream& out, const BinaryTree& bt) {
  bt.dump (out, bt.root, 0);
  return out;
}

void BinaryTree::dump (std::ostream& out, link t, int h) const {

  if (t == 0) {
    for (int i = 0; i < h; ++i) {
      out << " ";
    }
    out << "*" << std::endl;
    return;
  }

  dump (out, t->r, h+1);
  for (int i = 0; i < h; ++i) {
      out << " ";
  }
  out << t->item << std::endl;
  dump (out, t->l, h+1);
}

void BinaryTree::removeLeaf (Item r) {
  doRemoveLeaf (root, r);
}

bool doRemoveLeaf (BinaryTree::link t, Item r) {
  
  if (t->l == 0 && t->r == 0 && t->item == r) {
    return true;
  }

  bool u, v;
  u = v = false;
  
  if (t->l) u = doRemoveLeaf (t->l, r);
  if (t->r) v = doRemoveLeaf (t->r, r);

  if (u) {
    BinaryTree::link d = t->l;
    t->l = 0;
    delete d;
  }

  if (v) {
    BinaryTree::link d = t->r;
    t->r = 0;
    delete d;
  }
  return false;
}

int BinaryTree::countLeaf (void) {
  return isLeaf (root);
}

int BinaryTree::subTreeLeaf (link t) {
  int n_leaf = 0;
  if (t->l == 0 && t->r == 0) {
    return 1;
  }

  if (t->l) n_leaf += subTreeLeaf (t->l);
  if (t->r) n_leaf += subTreeLeaf (t->r);
  return n_leaf;
}

// count how many nodes with one child external
// and one child external are included in tree
int BinaryTree::countMix (void) {
  return subTreeMix (root);
}

//return true if t is a leaf, false otherwise
bool BinaryTree::isLeaf (link t) {

  if (t->l == 0 && t->r == 0) {
    return true;
  }
  return false;
}

// count how many nodes with one child external
// and one child external are included in the t subtree
int BinaryTree::subTreeMix (link t) {
  int n_mix = 0;

  if (isLeaf (t->l) == true && isLeaf (t->r) == true) {
    return 0;
  }
  
  if (isLeaf (t->l) == true && isLeaf (t->r) == false) {
    n_mix += 1 + subTreeMix (t->r);
  } else if (isLeaf (t->l) == false && isLeaf (t->r) == true) {
    n_mix += 1 + subTreeMix (t->l);
  } else {
    n_mix += subTreeMix (t->l);
    n_mix += subTreeMix (t->r);
  }
  return n_mix;
}
