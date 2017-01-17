#include "sorting.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

const int size = 10;



template<typename Item> void selectionSort(Item a[], int l, int r) {

  for (int i = l; i < r; i++) {
    int min = i;
    for(int j = i+1; j <= r; j++) {
      if (a[j] < a[min]) min = j;
    }
    int t = a[i];
    a[i] = a[min];
    a[min] = t;
  }
}

void testSorting (void) {

  int test[size];
  
  srand(time(0));
  for (int i = 0; i < size; ++i) test[i] = rand() % 1000;
  for (int i = 0; i < size; ++i) std::cout << test[i] << " ";
  std::cout << std::endl; 
  selectionSort(test, 0, size-1);
  for (int i = 0; i < size; ++i) std::cout << test[i] << " ";
  std::cout << std::endl; 
}
