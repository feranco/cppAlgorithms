#ifndef KEY_INDEXED_SEARCH_H
#define KEY_INDEXED_SEARCH_H

#include "symbol_table.h"

template <class Item, class Key>
  class KeyIdxSearch : public ST<Item, Key> {

  static const int max_idx = 1000;
  Item* arr;
  Item null_item;//needed to return null in search miss and select miss
  int n;

 public: 
  KeyIdxSearch ():n(0) {arr = new Item[max_idx];}
  ~KeyIdxSearch () {delete[] arr;}
  int count (void) {return n;} 
  void insert (Item item);
  Item search (Key k);
  void remove (Item item);
  Item select (int k);
  void visit (void);
};

template <class Item, class Key>
void KeyIdxSearch<Item,Key>::insert (Item item) {
  Key k = item.key();
  if (k < max_idx) arr[k] = item;
}

template <class Item, class Key>
void KeyIdxSearch<Item,Key>::remove (Item item) {
  Key k = item.key();
  if (k < max_idx) arr[k] = null_item;
}

template <class Item, class Key>
Item KeyIdxSearch<Item,Key>::search (Key k) {
  if (k < max_idx) return arr[k];
  else return null_item;
}

template <class Item, class Key>
Item KeyIdxSearch<Item,Key>::select (int k) {
  int cnt, i;
  if (k >= max_idx) return arr[k];
  
  for (cnt = 0, i = 0; i < max_idx; ++i) {
    if (!arr[i].null()) {
      //first increment and than compare in order to select k-th element
      if (++cnt == k) return arr[k];
    }
  }
  return null_item;
}

template <class Item, class Key>
void KeyIdxSearch<Item,Key>::visit (void) {
  for (int i = 0; i < max_idx; ++i) {
    if (!arr[i].null()) std::cout << arr[i];  
  }
}


#endif
