#ifndef MIN_HEAP
#define MIN_HEAP

template <class Item>
class MinHeap {
  int max_size;
  int size;
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
  
};

//bottom up procedure to restore min heap
//properties of k; heap[k/2] < heap[k]
template <class Item> 
void MinHeap<Item>::fixUp (int k) {
  if (k < 1 && k > size) return;
  Item item = heap[k];
  while (k > 1 && heap[k/2] > heap[k]) {
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
  
  while (2*k < size) {
    int j = 2*k;
    if (j < size && heap[j] > heap[j+1]) ++j;  //select smallest children
    if (item <= heap[j]) break;
    heap[k] = heap[j];
    k = j;
  }
  heap[k] = item;
}

template <class Item> 
bool MinHeap<Item>::empty (void) {
  return (size == 0);
}

template <class Item> 
bool MinHeap<Item>::insert (Item item) {
  if (size >= max_size) return false;
  heap[size++] = item;
  fixUp(size-1);
  return true;
}

template <class Item> 
Item MinHeap<Item>::min (void) {
  Item min = heap[1];
  heap[1] = heap[size]; 
  heap[size--] = min;
  return min;
}

#endif
