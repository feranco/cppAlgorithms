#include <iostream>
#include <fstream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include "symbol_table_data.h"

int main(int argc, char* argv[])
{
  StData d[10];
  for (int i = 0; i < 10; ++i) {
    d[i].rand();
    cout << d[i];
  }
  return 0;
}

 
