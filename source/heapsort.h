#ifndef HEAPSORT
#define HEAPSORT

//swap utility function
template <class Item>
void swap (Item arr[], int i, int j) {
  int tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

//top down function to restore heap properties
template <class Item>
void fixDown (Item arr[], int size, int k) {
  if (k < 1 || k > size) return;
  Item item = arr[k];
  while (2*k <= size) {
    int j = 2*k;
    if (j < size && arr[j] < arr[j+1]) ++j;
    if (item >= arr[j]) break;
    arr[k] = arr[j];
    k = j;
  }
  arr[k] = item;
}

template <class Item>
void heapsort (Item arr[], int size) {

  //heap order the array in O(n) time
  //the number of swap in fixDown is less than n
  //the number of comparison is the double in worst case
  for (int k = size/2; k >= 1; --k) {
    fixDown(arr, size, k);
  }

  //iteratively put the maximum in the last position
  //and reduce the heap by one; stop when k == 1
  //because the last element is already in its place 
  //worst case in O(nlogn): n call to fixDown, each call
  //performs logn swaps
  for (int k = size; k > 1; --k) {
    swap(arr,1,k);
    fixDown(arr, k-1, 1);
  }
}

void testHeapsort (void) {
  int size;
  srand(time(0));
  std::cout << "Insert array size " << std::endl;
  std::cin >> size;
  int* arr = new int[size+1];

  for (int i = 1; i <= size; ++i) {
    arr[i] = rand()%1000;
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;

  heapsort(arr, size);

  for (int i = 1; i <= size; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
  delete[] arr;
  
}

#endif
