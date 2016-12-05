#ifndef DOUBLE_QUEUE_H
#define DOUBLE_QUEUE_H

#include "queue.h"

class DoubleQueue {
 protected:
  void error(const char* err) const;
  virtual void dump(std::ostream& out) const = 0;
 public:
  virtual void  putFront(Item x) = 0;
  virtual Item  getFront(void) = 0;
  virtual void  putBack(Item x) = 0;
  virtual Item  getBack(void) = 0;
  friend  std::ostream& operator<<(std::ostream& out, const DoubleQueue& dq);
};

class DoubleQueueArray : public DoubleQueue {
  Item* dq;
  int size, head, tail;
  void dump(std::ostream& out) const;
 public:
  DoubleQueueArray(int sz);
  ~DoubleQueueArray(void);
  void  putFront(Item x);
  Item  getFront(void);
  void  putBack(Item x);
  Item  getBack(void);
};

class DoubleQueueList : public DoubleQueue {
  struct DoubleNode {
    Item item;
    DoubleNode *next, *prev;
    DoubleNode(Item x, DoubleNode* n, DoubleNode* p) {item = x; next = n; prev = p;} ;
  };

  typedef DoubleNode* link;
  link head, tail;
  
  void dump(std::ostream& out) const;
 public:
  DoubleQueueList();
  ~DoubleQueueList(void);
  void  putFront(Item x);
  Item  getFront(void);
  void  putBack(Item x);
  Item  getBack(void);
};

void testDoubleQueue(DoubleQueue* dq, const char* commands);

#endif
