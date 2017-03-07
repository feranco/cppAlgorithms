#include "testList.h"
#include "list.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

void testQuickSort (int n) {
  List<int> list;
  srand(time(0));
  for (int i = 0; i < n; ++i) {
    list.insertInFront(rand()%1000);
  }
  std::cout << list <<  std::endl;
  list.quicksort();
  std::cout << list <<  std::endl;
}

void testMergeSort (int n) {
  List<int> list;
  srand(time(0));
  for (int i = 0; i < n; ++i) {
    list.insertInFront(rand()%1000);
  }
  std::cout << list <<  std::endl;
  list.mergesort();
  std::cout << list <<  std::endl;
}
