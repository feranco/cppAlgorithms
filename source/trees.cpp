#include "trees.h"

BinaryTree::link BinaryTree::getRoot (void) {
  return root;
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

int BinaryTree::countLeaf (link t) {
  int n_leaf = 0;
  if (t->l == 0 && t->r == 0) {
    return 1;
  }

  if (t->l) n_leaf += countLeaf (t->l);
  if (t->r) n_leaf += countLeaf (t->r);
  return n_leaf;
}


//return true if t is a leaf, false otherwise
bool BinaryTree::isLeaf (link t) {

  if (t->l == 0 && t->r == 0) {
    return true;
  }
  return false;
}

// count how many nodes with one child external
// and one child external are included in the t tree
int BinaryTree::countMix (link t) {
  int n_mix = 0;

  if (isLeaf(t->l) == true && isLeaf(t->r) == true) {
    return 0;
  }
  
  if (isLeaf(t->l) == true && isLeaf (t->r) == false) {
    n_mix += 1 + countMix (t->r);
  } else if (isLeaf(t->l) == false && isLeaf(t->r) == true) {
    n_mix += 1 + countMix(t->l);
  } else {
    n_mix += countMix(t->l);
    n_mix += countMix(t->r);
  }
  return n_mix;
}

BinaryTree::BinaryTree (const char* s, const char* l) {
  root = preorderBuild(t, s++, l);
}

void BinaryTree::preorderBuild (link t, const char* s, const char* l) {
   static int i = 0;
   static int j = 0;
   if (s[i++] == '0') {
      t = new Node(l[j++]);
    }
    else {
      t = new Node(l[j++]);
      t-> l = preorderBuild(t->l, s, l);
      t-> r = preorderBuild(t->r, s, l);
    }
   return t;
}

void BinaryTree::preorderTraversal (void) {
  std::stack<link> s;
  s.push(root);
  while (!s.empty()) {
    link t = s.top();
    std::cout << t->item << " "; // print current node
    s.pop(); //pop it from the stack
    s.push(t->r); //push right subtree
    s.push(t->l); //push left subtree
  }
}

void BinaryTree::inorderTraversal (void) {
  std::stack<link> s;
  if (root->r) s.push(root->r);
  s.push(root);
  link t = root->l;

  while (!s.empty()) {
    while (t != 0) {
      s.push(t);
      t = t->l;
    }
    std::cout << s.top()->item;
    t = s.top()->r;
    s.pop();

    //if (s.empty()) std::cout << t->item; //s.push(t);
  }
}
/*
void BinaryTree::postorderTraversal (void) {
  link t = root;
  int i = 0;

  while (t!=0 || !s.empty()) {
    std::cout << ++i;
    while (t != 0) { // go to the left until is possible
      s.push(t->r);
      s.push(t);
      t = t->l;
    }
    
    t = s.top();
    s.pop();
    if(!t->r) {//p is a leaf
      std::cout << t->item << " ";
      t = 0;
    }
    else {
      link p = s.top();
      s.pop();
      s.push(t);
      t = p;
    }
  }
}
*/
void BinaryTree::postorderTraversal (void) {
  std::stack<link> s;
  link t = root;
  int i = 0;

  while (t!=0 || !s.empty()) {
    std::cout << ++i;
    while (t != 0) { // go to the left until is possible
      s.push(t->r);
      s.push(t);
      t = t->l;
    }
    
    t = s.top();
    s.pop();
    if(!t->r) {//p is a leaf
      std::cout << t->item << " ";
      t = 0;
    }
    else {
      link p = s.top();
      s.pop();
      s.push(t);
      t = p;
    }
  }
}


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
