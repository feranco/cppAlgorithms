#include "sorting.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

const int size = 1000;

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

template<typename Item> voidinsertionSort(Item a[], int l, int r) {

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
  for (int i = 0; i < size; ++i) test[i] = rand() % 10000;
  for (int i = 0; i < size; ++i) std::cout << test[i] << " ";
  std::cout << std::endl; 
  std::clock_t start = std::clock();
  selectionSort(test, 0, size-1);
  std::clock_t end = std::clock() - start;
  std::cout << "Time elapsed: "<< ((static_cast<double>(end-start)/CLOCKS_PER_SEC)/1000) << " ms" << std::endl; 
  for (int i = 0; i < size; ++i) std::cout << test[i] << " ";
  std::cout << std::endl; 
}

void testSortingCorners (void) {

  int test[size];
  std::clock_t start, end;
  
  srand(time(0));

  //already ordered
  for (int i = 0; i < size; ++i) test[i] = i;
  for (int i = 0; i < size; ++i) std::cout << test[i] << " ";
  std::cout << std::endl; 
  start = std::clock();
  selectionSort(test, 0, size-1);
  end = std::clock() - start;
  std::cout << "Time elapsed (already ordered): "<< ((static_cast<double>(end-start)/CLOCKS_PER_SEC)/1000) << " ms" << std::endl; 
  for (int i = 0; i < size; ++i) std::cout << test[i] << " ";
  std::cout << std::endl; 

  //inversely ordered
  for (int i = 0; i < size; ++i) test[i] = size-i;
  for (int i = 0; i < size; ++i) std::cout << test[i] << " ";
  std::cout << std::endl; 
  start = std::clock();
  selectionSort(test, 0, size-1);
  end = std::clock() - start;
  std::cout << "Time elapsed (already ordered): "<< ((static_cast<double>(end-start)/CLOCKS_PER_SEC)/1000) << " ms" <<  std::endl; 
  for (int i = 0; i < size; ++i) std::cout << test[i] << " ";
  std::cout << std::endl; 

  //same keys
  for (int i = 0; i < size; ++i) test[i] = 10;
  for (int i = 0; i < size; ++i) std::cout << test[i] << " ";
  std::cout << std::endl; 
  start = std::clock();
  selectionSort(test, 0, size-1);
  end = std::clock() - start;
  std::cout << "Time elapsed (already ordered): "<< ((static_cast<double>(end-start)/CLOCKS_PER_SEC)/1000) << " ms" << std::endl; 
  for (int i = 0; i < size; ++i) std::cout << test[i] << " ";
  std::cout << std::endl; 
  
  //two keys
  for (int i = 0; i < size; ++i) test[i] = rand() % 2;
  for (int i = 0; i < size; ++i) std::cout << test[i] << " ";
  std::cout << std::endl; 
  start = std::clock();
  selectionSort(test, 0, size-1);
  end = std::clock() - start;
  std::cout << "Time elapsed (already ordered): "<< ((static_cast<double>(end-start)/CLOCKS_PER_SEC)/1000) << " ms" << std::endl; 
  for (int i = 0; i < size; ++i) std::cout << test[i] << " ";
  std::cout << std::endl; 

  //one element array
  int testOne[1] = {10};
  start = std::clock();
  selectionSort(testOne, 0, 1);
  end = std::clock() - start;
  std::cout << "Time elapsed (already ordered): "<< ((static_cast<double>(end-start)/CLOCKS_PER_SEC)/1000) << " ms" << std::endl; 
  for (int i = 0; i < size; ++i) std::cout << test[i] << " ";
  std::cout << std::endl;

}
