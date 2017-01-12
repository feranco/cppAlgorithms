#include "trees.h"
#include <iostream>
#include <stdio.h>


using namespace std;

int main(int argc, char* argv[])
{
  //const char*s = "1100100";
  //const char*l = "cba*d*e";
  const char*s = "1100100";
  const char*l = "dbacfeg";
  BinaryTree bt(s, l);
  cout << bt;
  //cout << bt.countLeaf(bt.getRoot()) << endl;
  //cout << bt.countMix(bt.getRoot()) << endl;
  bt.preorderTraversal();
  bt.inorderTraversal();
  bt.postorderTraversal();

  levelorderTraversal();

  
  return 0;
}

