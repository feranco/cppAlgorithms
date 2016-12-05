#include "stack.h"
#include <iostream>
#include <stdio.h>


using namespace std;

int main(int argc, char* argv[])
{
  StackArray sl(100);
  Stack* s = &sl;
  testStack(s, "EAS*YQ**ESTIO*N");
  StackArray sl2 = sl;
  cout << "sl: " << sl;
  cout << "sl2cc: " << sl2;
  testStack(s, "PI*PPO");
  sl2 = sl;
  cout << "sl2=: " << sl2;
  
}




