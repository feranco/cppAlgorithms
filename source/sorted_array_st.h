#ifndef SORTED_ARRAY_ST_H
#define SORTED_ARRAY_ST_H

#include <iostream>
#include "symbol_table.h"

template <class Item, class Key>
class SortedArraySt : public ST<Item, Key> {
  static const int size = 1000;
  Item* arr;
  Item null_item;
  int n;
 public:
  SortedArraySt ():n(0) {arr = new Item[size];}
  ~SortedArraySt () {delete[] arr;}
  int count (void) {return n;}
  void insert (Item item);
  Item search (Key k);
  void remove (Item item);
  Item select (int k);
  void visit (void);
};

template <class Item, class Key>
void SortedArraySt<Item, Key>::insert (Item item) {
  if (n >= size) return;
  int i = n;
  Key k = item.key();//prevent many function call during while
  while (i > 0 && arr[i-1].key() > k) {
    arr[i] = arr[i-1];
    --i;
  }
  arr[i] = item;
  ++n;
}

template <class Item, class Key>
Item SortedArraySt<Item, Key>::search (Key k) {
  for (int i = 0; i < size; ++i) {
    if (arr[i].key() >= k) break;
  }
  if (i < size && arr[i].key() == k) return arr[i];
  return null_item;
}

template <class Item, class Key>
void SortedArraySt<Item, Key>::remove (Item item) {
  int i;
  for (i = 0; i < n; ++i) {
    if (arr[i].key() >= item.key()) break;
  }

  if (i < n && arr[i].key() ==  item.key()){
    for (i = i+1; i < size; ++i) arr[i-1] = arr[i];
    arr[--n] = null_item;
  }
}

template <class Item, class Key>
Item SortedArraySt<Item, Key>::select (int k) {
  if (k>=n) return null_item;
  else return arr[k];
}

template <class Item, class Key>
void SortedArraySt<Item, Key>::visit (void) {
  for (int i = 0; i < n; ++i) {
    std::cout << arr[i];
  }
}

#if 0
template <class Item, class Key>
void SortedArraySt<Item, Key>::remove (Item item) {
  int i = 0;
  while (i < n && arr[i].key() < item.key()) ++i;
  if (i < n && arr[i].key() == item.key()) {
    for (i = i+1; i < n; ++i) arr[i-1] = arr[i];
    arr[--n] = null_item;
  }
}
#endif
#endif
