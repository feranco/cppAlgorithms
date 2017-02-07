#include "list.h"
#include <iostream>

using namespace std;
#include <ctime>
#include <cstdlib>

int main(int argc, char* argv[])
{
  List<int> list;
  srand(time(0));
  for (int i = 0; i < 15; ++i) {
    list.insertInFront(rand()%1000);
  }
  cout << list << endl;
  list.quicksort();
cout << list << endl;
  return 0;
}

