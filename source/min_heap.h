#ifndef MIN_HEAP
#define MIN_HEAP

#include <iostream>

template <class Item>
class MinHeap {
  int max_size;
  int size;  //current size, index of last inserted element 
  Item* heap;
  void fixUp (int k);
  void fixDown (int k);

 public:
  MinHeap (int max_size): max_size(max_size), size(0) {heap = new Item[max_size+1];}
  MinHeap (Item arr[], int size): max_size(size), size(size) {heap =arr;}
  ~MinHeap () {if (heap) delete[] heap;}
  Item min (void);
  bool insert (Item item);
  bool empty (void);
  void dump(void);
  
};

//bottom up procedure to restore min heap
//properties of k; heap[k/2] < heap[k]
template <class Item> 
void MinHeap<Item>::fixUp (int k) {
  if (k < 1 || k > size) return;
  Item item = heap[k];
  while (k > 1 && heap[k/2] > item) {
    heap[k] = heap[k/2];
    k = k/2;
  }
  heap[k] = item;
}

//top down procedure to restore min heap
//properties of k; heap[k] > heap[2*k] && heap[k] > heap[2*k+1]
template <class Item> 
void MinHeap<Item>::fixDown (int k) {

  if (k < 1) return;
  Item item = heap[k];
  
  while (2*k <= size) {
    int j = 2*k;
    if (j < size && heap[j] > heap[j+1]) ++j;  //select smallest children avoiding bad access
    if (item <= heap[j]) break;  //exit if none of the children is smaller
    heap[k] = heap[j];
    k = j;
  }
  heap[k] = item;
}

template <class Item> 
bool MinHeap<Item>::empty (void) {
  return (size == 0);
}

//insert a new element in the right position
template <class Item> 
bool MinHeap<Item>::insert (Item item) {
  if (size >= max_size) return false;
  heap[++size] = item;//first increase then insert
  fixUp(size);
  return true;
}

//remove and return the minimum
template <class Item> 
Item MinHeap<Item>::min (void) {
  Item min = heap[1];
  heap[1] = heap[size]; 
  heap[size--] = min;
  fixDown(1);
  return min;
}

//print heap by layers
template <class Item> 
void MinHeap<Item>::dump (void) { 
  int p2 = 2;
  for (int k = 1; k <= size; ++k) {
    if (k == p2) {
      std::cout << std::endl;
      p2 *=2;
    }
    std::cout << heap[k] << " ";
  }
  td::cout << std::endl;
}

#endif
