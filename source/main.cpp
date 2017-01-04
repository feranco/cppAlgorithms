#include "trees.h"
#include <iostream>
#include <stdio.h>


using namespace std;

int main(int argc, char* argv[])
{
  int array[] = {8,4,5,2,9};
  BinaryTree bt;
  bt.Tournament (array, 0, 4); 
  cout << bt;
  cout << "SSSSSSSSSSSS" <<endl;
  cout << bt.countLeaf() << endl;
  cout << bt.countMix() << endl;
  bt.inorderTraversal();
  //out << bt.subTreeMix(this->root) << endl;
  //bt.removeLeaf (2);
  //cout << bt;
  //cout << bt.countLeaf() << endl;
  //cout << bt.countMix() << endl;
}




