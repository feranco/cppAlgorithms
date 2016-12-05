#ifndef RANDOM_QUEUE_H
#define RANDOM_QUEUE_H

#include "queue.h"

class RandomQueueArray : public MyQueue {
  Item* rq;
  int size;
  int tail;

public:
  RandomQueueArray(int sz);
  ~RandomQueueArray();
  void put(Item x);
  void putIgnoreNew(Item x);
  void putForgetOld(Item x);
  Item get(void);
  void dump(std::ostream& out) const;
};

class RandomQueueList : public MyQueue {
  struct Node {
    Item  item;
    Node* next;
    Node(Item x, Node* n) { item = x; next = n;};
  };

  typedef Node* link;
  int size;
  link head;

public:
  RandomQueueList();
  ~RandomQueueList();
  void put(Item x);
  void putIgnoreNew(Item x);
  void putForgetOld(Item x);
  Item get(void);
  Item getReservoirSample(void);
  void dump(std::ostream& out) const;
};

void testRandomQueue(MyQueue* q, int n);

#endif
