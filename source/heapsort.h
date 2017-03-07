#ifndef HEAPSORT
#define HEAPSORT

template <class Item>
void heapsort (Item arr[], int size) {

  //heap order the array in O(n) time
  //the number of swap in fixDown is less than n
  //the number of comparison is the double in worst case
  for (int k = size/2; k >= 1; --k) {
    fixDown(arr, k);
  }
  /*
  for (int k = 1; k <= size; ++k) {
    int max = arr[1];
    arr[1] = arr[size];
    arr[size--] = max;
    fixDown(arr,1);
    }*/

  //iteratively put the maximum in the last position
  //and reduce the heap by one; stop when k == 1
  //because the last element is already in its place
  for (int k = size; k > 1; --k) {
    swap(1,k);
    fixDown(arr,1);
  }
}

#endif
