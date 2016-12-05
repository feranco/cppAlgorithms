#ifndef STACK_H
#define STACK_H

#include <iostream>

typedef char Item;

class Stack {

 public:
  virtual void push(Item x) = 0;
  virtual void pop(void) = 0;
  void error(const char* err);
  virtual Item top(void) = 0;
  int  count(void);
  virtual void dump(std::ostream& out) const = 0;
  friend std::ostream& operator<<(std::ostream& out, const Stack& rhs);
};

void testStack(Stack* s, const char* commands);

// Stack implementation with linked list 
class StackList : public Stack {
  struct Node {
    Item  item;
    Node* next;
    Node(Item  item, Node* next) { this->item = item; this->next = next; };
  };

  typedef Node* link;

  link stack; //top of the stack ptr
  int n; //current size

 public:
  StackList();
  ~StackList();
  StackList(const StackList& sl);
  void push(Item x);
  void pop(void);
  Item top(void);
  int  count(void);
  void dump(std::ostream& out) const;
  StackList& operator=(const StackList& sl);
};

class StackArray : public Stack {
  Item* stack;
  int size;
  int tos;

 public:
  StackArray(int sz);
  ~StackArray();
  StackArray(const StackArray& sa);
  void push(Item x);
  void pop(void);
  Item top(void);
  void dump(std::ostream& out) const;
  StackArray& operator=(const StackArray& sa);
};


class DualStack {
  Item* dualstack;
  int size;
  int tos1;
  int tos2;

 public:
  DualStack(int sz);
  ~DualStack();
  void push1(Item x);
  void push2(Item x);
  void pop1();
  void pop2();
  Item top1();
  Item top2();
  bool empty1();
  bool empty2();
 };

int testDualStack(const char* infix);

#endif
