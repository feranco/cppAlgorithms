#include "trees.h"
#include <iostream>
#include <stdio.h>


using namespace std;

int main(int argc, char* argv[])
{
  /*
  int array[] = {8,4,5,2,9};
  BinaryTree bt;
  bt.Tournament (array, 0, 4); 
  cout << bt;
  cout << "SSSSSSSSSSSS" <<endl;
  cout << bt.countLeaf(bt.getRoot()) << endl;
  cout << bt.countMix(bt.getRoot()) << endl;
  bt.postorderTraversal();
  //out << bt.subTreeMix(this->root) << endl;
  //bt.removeLeaf (2);
  //cout << bt;
  //cout << bt.countLeaf() << endl;
  //cout << bt.countMix() << endl;
  */

  //char s[] = {'1','1','0','1','0'};
  //char l[] = {'c','b','a','*','d','*','e'};
  const char*s = "1100100";
  const char*l = "cba*d*e";
  BinaryTree bt(s, l);
  cout << bt;
  return 0;
}

