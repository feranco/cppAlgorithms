#ifndef MAX_HEAP
#define MAX_HEAP

#include <vector>
#include <iostream>


template <class Item>
class MaxHeap {
  std::vector<Item> heap;
  void fixUp (int k);
  void fixDown (int k);
  
 public:
  MaxHeap () {};
  void insert (Item item);
  Item max (void);
  void empty (void) const;
  void dump (void) const;
};

template <class Item>
void MaxHeap<Item>::fixUp (int k) {
  Item item = heap[k];
  //(k-1) / 2 is the parent
  while (k > 0 && heap[(k-1)/2] < item) {
    heap[k] = heap[k/2];
    k = (k-1) / 2;
  }

  heap[k] = item;
}

template <class Item>
void MaxHeap<Item>::fixDown(int k) {
  Item item = heap[k];

  //(2*k)+1 is the left child
  while ((2*k)+1 < heap.size()-1) {
    int j = (2*k)+1;
    if (j < (heap.size()-1) && heap[j] < heap[j+1]) ++j;
    if (item >= heap[j]) break;
    heap[k] = heap[j];
    k = j;
  }
  heap[k] = item;
}

template <class Item>
void MaxHeap<Item>::empty(void) const {
  return heap.empty();
}

template <class Item>
void MaxHeap<Item>::insert(Item item) {
  heap.push_back(item);
  fixUp(heap.size()-1);
}

template <class Item>
Item MaxHeap<Item>::max(void) {
  Item max = heap[0];
  heap[0] = heap.size()-1;
  heap.pop_back();
  fixDown(0);
  return max;
}

//print heap by layers
template <class Item> 
void MaxHeap<Item>::dump (void) const { 
  int p2 = 2;
  int k = 1;
  typename std::vector<Item>::const_iterator it;
  for (it = heap.begin(); it != heap.end(); ++it) {
    if (k == p2) {
      std::cout << std::endl;
      p2 *=2;
    }
    std::cout << *it << " ";
    ++k;
  }
  std::cout << std::endl;
}

#include <ctime>
#include <cstdlib>

void testMaxHeap (void) {
  const int size = 16;
  srand(time(0));
  MaxHeap<int> min_heap;
  //MaxHeap<int> min_heap(); error ()  compiler thinks of min_heap
  //as of function declaration
  std::cout << "Insert " << size << std::endl;
  for (int i = 0; i < size; ++i) {
    min_heap.insert(rand()%1000);
  }
  min_heap.dump();

  std::cout << "Remove " << size/2 << std::endl;
  for (int i = 0; i < size/2; ++i) {
    std::cout << min_heap.max() << " ";
  }
  std::cout << std::endl;
  //min_heap.dump();

  std::cout << "Insert " << size/2 << std::endl;
  for (int i = 0; i < size/2; ++i) {
     min_heap.insert(rand()%1000);
  }
  std::cout << std::endl;
  //min_heap.dump();

  std::cout << "Remove all" << std::endl;
  for (int i = 0; i < size; ++i) {
    std::cout << min_heap.max() << " ";
  }
  std::cout << std::endl;
  //min_heap.dump();
}


#endif
