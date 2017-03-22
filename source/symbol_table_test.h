#ifndef SYMBOL_TABLE_TEST
#define SYMBOL_TABLE_TEST


#include <iostream>
#include "symbol_table_data.h"
#include "symbol_table.h"

const int sz = 10;

template <class Item, class Key>
void testST (ST<Item,Key>& st) {
  StData item;
  for (int i = 0; i < sz; ++i) {
    item.rand();
    if (st.search(item.key()).null()) st.insert(item);   
  }
  st.visit();
  Item x = st.search(item.key());
  std::cout << "search hit: " << x;
  st.remove(x);
  std::cout << "HHH";
  x = st.search(x.key());
  std::cout << "search miss: " << x;
  st.visit();
}

#endif
