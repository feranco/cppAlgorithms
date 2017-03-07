#include "min_heap.h"
#include <iostream>

using namespace std;
#include <ctime>
#include <cstdlib>

void testMinHeap (void) {
  const int size = 16;
  srand(time(0));
  MinHeap<int> min_heap(size);

  std::cout << "Insert " << size << std::endl;
  for (int i = 0; i < size; ++i) {
    min_heap.insert(rand()%1000);
  }
  min_heap.dump();

  std::cout << "Remove " << size/2 << std::endl;
  for (int i = 0; i < size/2; ++i) {
    std::cout << min_heap.min() << " ";
  }
  std::cout << std::endl;
  min_heap.dump();

  std::cout << "Insert " << size/2 << std::endl;
  for (int i = 0; i < size/2; ++i) {
     min_heap.insert(rand()%1000);
  }
  std::cout << std::endl;
  min_heap.dump();

  std::cout << "Remove all" << std::endl;
  for (int i = 0; i < size/2; ++i) {
    std::cout << min_heap.min() << " ";
  }
  std::cout << std::endl;
  min_heap.dump();
}

int main(int argc, char* argv[])
{
  testMinHeap();
  return 0;
}

