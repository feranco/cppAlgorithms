#ifndef FIFO_H
#define FIFO_H

#include "queue.h"

// FIFO implementation with linked list 
class FIFOList : public MyQueue {
  
  struct Node {
    Item  item;
    Node* next;
    Node(Item  item) { this->item = item; this->next = 0; }; //insert only in tail, so next = 0
  };
  typedef Node* link;
  link head, tail;

public:
  FIFOList();
  ~FIFOList();
  virtual void put(Item x);
  virtual void putIgnoreNew(Item x);
  virtual void putForgetOld(Item x);
  Item get(void);
  void dump(std::ostream& out) const;
};

//FIFO implementation with array
class FIFOArray : public MyQueue {
  Item* fifo;
  int size;
  int head;
  int tail;

public:
  FIFOArray(int sz);
  ~FIFOArray();
  virtual void put(Item x);
  virtual void putIgnoreNew(Item x);
  virtual void putForgetOld(Item x);
  Item get(void);
  void dump(std::ostream& out) const;
  FIFOArray(const FIFOArray& fa);
  FIFOArray& operator=(const FIFOArray& fa);
};

#endif
