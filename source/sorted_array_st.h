#ifndef SORTED_ARRAY_ST_H
#define SORTED_ARRAY_ST_H

template <class Item, class Key>
class SortedArraySt : public ST<Item, Key> {
  static const int size = 1000;
  Item* arr;
  Item null_item;
  int n;
 public:
  SortedArraySt ():n(0) {arr = new Item[size];}
  ~SortedArraySt () {delete[] arr;}
};

#endif
