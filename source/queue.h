#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

typedef char Item;

//generic queue interface
class MyQueue {
public:
  virtual void put(Item x) = 0;
  virtual Item get(void) = 0;
  virtual void putIgnoreNew(Item x) = 0;
  virtual void putForgetOld(Item x) = 0;
  void error(const char* err) const;
  virtual void dump(std::ostream& out) const = 0;
  friend std::ostream& operator<<(std::ostream& out, const MyQueue& fifo);
};

#endif
