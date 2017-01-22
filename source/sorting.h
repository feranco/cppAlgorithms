#ifndef SORTING_H
#define SORTING_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

//selection sort implementation
//scan the array through the i index
//at each step the left element of i are ordered
//the minimum element right to i is selected and inserted in i position
template<typename Item> void selectionSort(Item a[], int l, int r) {

  for (int i = l; i < r; i++) {
    int min = i;
    for(int j = i+1; j <= r; j++) {
      if (a[j] < a[min]) min = j;
    }
    Item t = a[i];
    a[i] = a[min];
    a[min] = t;
  }
}

//insertion sort implementation
//scan the array through the i index
//at each step the left element of i are ordered
//the i element is inserted between its left elements in the right place
template<typename Item> void insertionSort(Item a[], int l, int r) {
  //scan the input array
  for (int i = l+1; i <= r; i++) {
    int j = i;
    Item t = a[i];
    //find the place where to insert the current element
    while (t < a[j-1] && j > l) {
      a[j] = a[j-1];   
      j--;
    }
    a[j] = t;
  }
}

//bubble sort implementation
//scan the array through the i index
//at each step the left element of i are ordered
//back-scan the array through the j index
//at each step the j element is swapped with the j-1 if this is bigger 
//the j element is inserted in order in i position
template<typename Item> void bubbleSort(Item a[], int l, int r) {
  int count = 0;
  for (int i = l; i < r; i++) {
    bool ordered;
    for (int j = r; j > i; j--) {
      ordered  = true;
      if (a[j] < a[j-1]) {
	Item t = a[j];
	a[j] = a[j-1];
	a[j-1] = t;
	ordered = false;
	count++;
      }
    }
    if (ordered) {std::cout << i << std::endl; break;}
  }
  std::cout << count << std::endl;
}

//shell sort implementation
//h-order the array for decreasing h
//scan the array through the i index
//at each step the left element of i are h-ordered
//the i element is inserted between its left elements in the right place
template<typename Item> void shellSort(Item a[], int l, int r) {
  int max = 1;
  //initialize the max increment according to the array size
  while (max <= (r-l)/3) max = 3*max+1;
   std::cout << max << std::endl;
   
  //h-ordering the array for decreasing h
  for (int h = max; h >= 1; h=h/3) {
    //std::cout << h << std::endl;
     //h-ordering the array for the current h
    for (int i = h; i <= r; i++) {
      Item t = a[i];
      int j = i;
      //find the place of the current element in the h-ordered array
      while (t < a[j-h] && j>=h) {
	a[j] = a[j-h];
	j-=h;
      }
      a[j] = t;
    }
    //for (int i = 0; i <= r; ++i) std::cout << a[i] << " ";
    //std::cout << std::endl; 
  }
  
}


#endif
