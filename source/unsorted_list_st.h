#ifndef SORTED_ARRAY_ST_H
#define SORTED_ARRAY_ST_H

#include <iostream>
#include "symbol_table.h"

template <class Item, class Key>
class UnsortedListSt : public ST<Item, Key> {
  struct Node {
    Item  item;
    Node* next;
    Node (Item x):item(x), next(0){} 
  };
  typedef Node* Link;
  Item null_item;
  Link head;
  int n;
 public:
  UnsortedListSt (void):head(0){}
  //~UnsortedListSt ();
  int count (void) {return n;}
  void insert (Item item);
  Item search (Key k);
  void remove (Item item);
  Item select (int k);
  void visit (void);
};

template <class Item, class Key>
void UnsortedListSt<Item, Key>::insert (Item item) {
  Link tmp = new Node(item);
  tmp->next = head;
  head = tmp;
}

template <class Item, class Key>
Item UnsortedListSt<Item, Key>::search (Key k) {
  Link tmp = head;
  while (tmp) {
    if(tmp->item.key() == k) return tmp->item;
    tmp = tmp->next;
  }
  return null_item;
}

template <class Item, class Key>
void UnsortedListSt<Item, Key>::remove (Item item) {
  Key k = item.key();
  Link tmp = head;
  
  if (head && head->item.key() == k) {
    head = tmp->next;
    delete tmp;
  }

  while (tmp->next) {
    if (tmp->next->item.key() == k) {
      Link rm = tmp->next;
      tmp->next = rm->next;
      delete rm;
      break;
    }
  }  
}

template <class Item, class Key>
Item UnsortedListSt<Item, Key>::select (int k) {
  //first sort the list and than return the k-th node
  return null_item;
}

template <class Item, class Key>
void UnsortedListSt<Item, Key>::visit (void) {
  //first sort the list and then print nodes
}

#endif
