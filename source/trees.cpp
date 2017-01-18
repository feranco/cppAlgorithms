#include "trees.h"
#include <cstring>
#include <queue>
#include <stack>
#include <utility>

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
  out << (char)t->item << std::endl;
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

  if(!t) return false;

  if (t->l == 0 && t->r == 0) {
    return true;
  }
  else {
    return false;
  }
}

// count how many nodes with one child external
// and one child external are included in the t tree
int BinaryTree::countMix (link t) {
  int n_mix = 0;
  //t is a leaf
  if (!t || (isLeaf(t->l) == true && isLeaf(t->r) == true)) {
    return 0;
  }

  
  if (isLeaf(t->l) == true && isLeaf (t->r) == false) {
    n_mix += 1 + countMix (t->r); //t is a mix without r 
  } else if (isLeaf(t->l) == false && isLeaf(t->r) == true) {
    n_mix += 1 + countMix(t->l); //t is a mix without l
  } else {
    n_mix += countMix(t->l); //t is internal
    n_mix += countMix(t->r);
  }
  return n_mix;
}

int BinaryTree::internalPathLength (link t, int l) {

  if(!t || isLeaf(t)) {
    return 0;
  }
  else {
    return l + internalPathLength(t->l, l+1) + internalPathLength(t->r, l+1);
  }
}

BinaryTree::BinaryTree (const char* s, const char* l) {
  root = preorderBuild(root, s, l);
}

BinaryTree::link BinaryTree::preorderBuild (link t, const char* s, const char* l) {
   static int i = 0;
   static int j = 0;
   if (s[i++] == '0') {
      t = new Node(l[j++]);
      if (t->item == '*') t = 0; //Set fake nodes to null
    }
    else {
      t = new Node(l[j++]);
      t-> l = preorderBuild(t->l, s, l);
      t-> r = preorderBuild(t->r, s, l);
    }
   return t;
}

//preorder traversal without recursion
void BinaryTree::preorderTraversal (void) {
  std::stack<link> s;
  s.push(root);
  while (!s.empty()) {
    link t = s.top();
    std::cout << t->item << " "; // print current node
    s.pop(); //pop it from the stack
    if (t->r) s.push(t->r); //push right subtree
    if (t->l) s.push(t->l); //push left subtree
  }
}

//inorder traversal without recursion
void BinaryTree::inorderTraversal (void) {
  std::stack<link> s;
  link t = root;
  bool done = false;

  while (!done) {
    while (t != 0) { //explore left and push until possible
      s.push(t);
      t = t->l;
    }

    if (s.empty()) {
      done = true;
    }
    else
    {
      std::cout << s.top()->item << " "; //print top
      t = s.top()->r; //explore right 
      s.pop();
    }
  }
}

void BinaryTree::postorderTraversal (void) {
  std::stack<link> s;
  link t = root;
  bool done = false;

  while (!done) {
    while (t) { //explore left until possible
      if (t->r) s.push(t->r); //push right
      s.push(t); //push node
      t = t->l;
    }
    
    t = s.top();
    s.pop();
    if (t->r && t->r == s.top()) { //t has right child not explored
      //link p = s.top();
      s.pop();
      s.push(t);
      t = t->r;
    }
    else { //t is a leaf, a node without right or with right explored
      std::cout << t->item << " ";
      t = 0;
    }
    if (s.empty()) done = true;
  }
}

void testTreeTraversal (void) {
  //const char*s = "1100100";
  //const char*l = "cba*d*e";
  //const char*s = "1100100";
  //const char*l = "dbacfeg";
  //BinaryTree bt(s, l);
  //std::cout << bt;
  //std::cout << bt.countLeaf(bt.getRoot()) << std::endl;
  //std::cout << bt.countMix(bt.getRoot()) << std::endl;
  //bt.preorderTraversal();
  //bt.inorderTraversal();
  //bt.postorderTraversal();
  const char*s = "11100011000";
  const char*l = "edbac*hf*g*";
  BinaryTree bt(s, l);
  std::cout << bt;
  std::cout << bt.internalPathLength(bt.getRoot(),0);
}

void testLevelorderTraversal (void) {
  const char*s = "DBACFEG";
  const char*l = "ABCDEFG";
  //const char*s = "CBADE";
  //const char*l = "ABCDE";
  levelorderTraversal(s,l);
}

// build level order traversal from prorder and inorder
void levelorderTraversal (const char* preOrder, const char* inOrder) {
  std::queue<char> levOrder; //level order fifo: each node splits inorder in two intervals  
  std::queue<int> inOrderLBound, inOrderUBound; //bound of the inorder intervals 
  std::queue<int> preOrderIdx; //index used to pick next node to insert in levOrder
  char node;
  int nodeInOrder, currLBound, currUBound, currIdx;

  //put the root and initialize other fifo accordingly
  levOrder.push(preOrder[0]);
  inOrderLBound.push(0);
  inOrderUBound.push(strlen(inOrder) - 1);
  preOrderIdx.push(0);

  while (!levOrder.empty()) {
    //get element from fifo queues
    node = levOrder.front();
    currLBound = inOrderLBound.front();
    currUBound = inOrderUBound.front();
    currIdx = preOrderIdx.front() + 1;
    levOrder.pop();
    inOrderLBound.pop();
    inOrderUBound.pop();
    preOrderIdx.pop();
    
    //print nodes in level order
    std::cout << node << " ";

    //search the index of the node in the curent inorder interval
    nodeInOrder = 0;
    for (int i = currLBound; i <= currUBound; ++i) {
      if (node == inOrder[i]) nodeInOrder = i;
    }

    //compute the size of the two intervals
    int sizeL = nodeInOrder - currLBound;
    int sizeR = currUBound - nodeInOrder;

    // put a node if the left interval is not empty
    if (sizeL > 0) {
      levOrder.push(preOrder[currIdx]);
      inOrderLBound.push(currLBound);
      inOrderUBound.push(nodeInOrder-1);
      preOrderIdx.push(currIdx);
    }

    // put a node if the right interval is not empty
    if(sizeR) {
      levOrder.push(preOrder[currIdx + sizeL]);
      inOrderLBound.push(currLBound + sizeL + 1);
      inOrderUBound.push(currUBound);
      preOrderIdx.push(currIdx + sizeL);
    }

  }
}

