#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

template <class Item, class Key>
class ST {
 public:
  virtual int count (void) = 0; 
  virtual void insert (Item item) = 0;
  virtual Item search (Key k) = 0;
  virtual void remove (Item item) = 0;
  virtual Item select (int k) = 0;
  virtual void visit (void) = 0;
};



#endif
