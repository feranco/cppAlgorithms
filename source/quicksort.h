#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include <stack>

//return the index of the pivot in the right place
template<typename Item> int partition(Item a[], int l, int r) {
  Item pivot = a[r];
  int i = l-1;
  int j = r;

  while (i < j) {
    while (a[++i] < pivot);
    while (a[--j] > pivot && j >l ); //if(j==l) break;
    if(i < j) {
      Item tmp = a[i];
      a[i] = a[j];
      a[j] = tmp;
    }
  }
  a[r] = a[i];
  a[i] = pivot;
  return i;
}

//standard quick sort implementation
template<typename Item> void quicksort(Item a[], int l, int r) {
 
  if (l>=r) return;   //end if size <= 1
  int pivot = partition (a, l, r); //put the pivot in the right place and return its index
  quicksort (a, l, pivot-1);
  quicksort (a, pivot+1, r);
}

//iterative quicksort implementation
template<typename Item> void quicksortIt (Item a[], int l, int r) {
  std::stack<int> bounds;
  int pivot;
  bool pop = false;

  do{
    //pop l and r
    if(pop) {
      r = bounds.top();
      bounds.pop();
      l = bounds.top();
      bounds.pop();
    }

    pivot = partition (a, l, r);
    pop = true;

    //push the bigger subset first
    if ((pivot-l) > (r-pivot)) {
      //stop if r <= l
      if ((pivot-1) > l) {
	bounds.push (l);
	bounds.push (pivot-1);
      }
      //stop if r <= l
      //set l without push into the stack
      if (r > (pivot+1)) {
	l = pivot+1;
	pop = false;
      }  
    }
    else {
      //stop if r <= l
      if (r > (pivot+1)) {
	bounds.push (pivot+1);
	bounds.push (r);
      }
      //stop if r <= l
      //set r without push into the stack
      if ((pivot-1) > l) {
	r = pivot-1;
	pop = false;
      }
    }
  }while (!bounds.empty());
}

//utility function that swap two array element
template<typename Item> void swap (Item a[], int i, int j) {
  Item tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

//select the pivot as the median of five and put the pivot in r-2
template<typename Item> void medianOfFive (Item a[], int l, int r) {
  Item idx[] = {l, (3*l+r)/4, (l+r)/2, (3*r+l)/4, r};

  //a0 < a1
  if (a[idx[0]] > a[idx[1]]) swap(a, idx[0], idx[1]);

  //a2 < a3
  if (a[idx[2]] > a[idx[3]]) swap(a, idx[2], idx[3]);

  //a0 is the smallest
  if (a[idx[0]] > a[idx[2]]) {
    swap(a, idx[0], idx[2]);
    swap(a, idx[1], idx[3]);
  }

  //a1 < a4
  if (a[idx[1]] > a[idx[4]]) swap(a, idx[1], idx[4]);

  //a1 is the smallest
  if (a[idx[1]] > a[idx[2]]) {
    swap(a, idx[1], idx[2]);
    swap(a, idx[3], idx[4]);
  }

  //a2 is the median
  if (a[idx[2]] > a[idx[4]]) {
    swap(a, idx[2], idx[4]);
  }
  
  swap(a, idx[1], l+1);
  swap(a, idx[2], r-2);
  swap(a, idx[3], r-1);
}

//quicksort implementation improved with median of five
//and not ordering subset with less than 11 elements
template<typename Item> void quicksortImp (Item a[], int l, int r) {

  //stop recursion if size of a is
  //less than minimum subset size
  static const int minSubset = 11;
  if ((r-l) < minSubset) {std::cout << r-l << " ret " << std::endl; return;}
  for (int i = l; i <= r; ++i) std::cout << a[i] << " ";
  std::cout << std::endl; 
  medianOfFive(a,l,r);
  int pivot = partition(a,l+2, r-2);
  quicksortImp(a, l, pivot-1);
  quicksortImp(a, pivot+1, r);
}

//quicksort + insertionsort implementation
template<typename Item> void hybridsort (Item a[], int l, int r) {
  quicksortImp(a, l, r);
  for (int i = l; i <= r; ++i) std::cout << a[i] << " ";
  std::cout << std::endl; 
  insertionSort(a, l, r);
}

#endif
