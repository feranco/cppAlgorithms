#include "stack.h"
#include <cstring>
//global functions

std::ostream& operator<<(std::ostream& out, const Stack& rhs) {
  rhs.dump(out);
  return out;
}

void testStack(Stack* s, const char* commands) {
  const char* cmd = commands;
  while(*cmd != 0) {

    if (*cmd == '*') {
      s->pop();
    }

    if (isupper(*cmd)) {
      s->push(*cmd);
    }

    std::cout << *s;
    cmd++;
  }
}

//Base class commun functions
void Stack::error(const char* err) {
  std::cout << err << std::endl;
}

//MyStack implementation with array
StackArray::StackArray(int sz) {
  stack = new Item[sz];
  size = sz;
  tos = 0;
}

StackArray::~StackArray() {
  delete[] stack;
}

StackArray::StackArray(const StackArray& sa): size(sa.size), tos(sa.tos) {
  stack = new Item[size];
  for (int i=0; i<tos; ++i) stack[i] = sa.stack[i];
}

void StackArray::push(Item x) {
  if(tos == size) {
    error("Stack full!");
  }
  else {
    stack[tos++] = x;
  }
}

void StackArray::pop(void) {
  if(tos == 0) {
    error("Stack empty");
  }
  else {
    --tos;
  }
}

Item StackArray::top(void) {
  return stack[tos-1];
}

void StackArray::dump(std::ostream& out) const {
  for (int i = 0; i<tos; ++i) {
    out << stack[i] << " ";
  }
  out << std::endl;
}

StackArray& StackArray::operator=(const StackArray& sa) {
  if (&sa != this) {
    delete[] stack;
    stack = new Item[sa.size];
    for (int i=0; i<sa.tos; ++i) {
      stack[i] = sa.stack[i];
    }
  }
  return *this;
}

//MyStack implementation with linked list
StackList::StackList() {
  n = 0;
  stack = 0;
}

StackList::~StackList() {
  link head = stack;
  while (head != 0) {
    link t = head;
    head = t->next;
    delete t;
  }
}

void StackList::push(Item x) {
  link t = new Node(x, stack);
  if(t) {
    stack = t;
    ++n;
  }
  else {
    error("Stack full!");
  }
}

void StackList::pop(void) {

  if(n > 0) {
    link t = stack;
    stack = t->next;
    --n;
    delete t;
  }
  else {
    error("Stack empty!");
  }
}

Item StackList::top(void) {
  return stack->item;
}

int StackList::count(void) {
  return n;
}

void StackList::dump(std::ostream& out) const {
  for (link t = stack; t!=0; t=t->next) {
    out << t->item << " ";
  }
  out << std::endl;
}

StackList::StackList(const StackList& sl) : stack(0), n(0) {
  if(sl.stack) {
    stack = new Node(sl.stack->item,0);
    link n = stack;
    for (link t = sl.stack->next; t!=0; t=t->next) {
      n->next = new Node(t->item, 0);
      n = n->next;
    }
  }
}

StackList& StackList::operator=(const StackList& sl) {
  if (&sl!=this) {
    //delete old stack
    while (stack!=0) {
      link t = stack;
      stack = t->next;
      delete t;
    }
    //create new stack
    if (sl.stack) {
      stack = new Node(sl.stack->item,0);
      link n = stack;
      for (link t = sl.stack->next; t!=0; t=t->next) {
	n->next = new Node(t->item, 0);
	n = n->next;
      }
    }
  }
  return *this;
}

/***************************
Dual Stack implementation with array
***************************/

DualStack::DualStack(int sz) {
  dualstack = new Item[sz];
  size = sz;
  tos1 = 0;
  tos2 = sz-1;
}

DualStack::~DualStack() {
  delete[] dualstack;
}

void DualStack::push1(Item x) {
  if(tos1 == tos2) {
    std::cout << "Stack full!" <<std::endl;
  }
  else {
    dualstack[tos1++] = x;
  }
}

void DualStack::push2(Item x) {
  if(tos1 == tos2) {
    std::cout << "Stack full!" <<std::endl;
  }
  else {
    dualstack[tos2++] = x;
  }
}

void DualStack::pop1() {
  if(tos1 == 0) {
    std::cout << "Stack empty!" <<std::endl;
  }
  else {
    --tos1;
  }
}

void DualStack::pop2() {
  if(tos2 == size-1) {
    std::cout << "Stack empty!" <<std::endl;
  }
  else {
    --tos2;
  }
}

Item DualStack::top1() {
  return dualstack[tos1-1];
}

Item DualStack::top2() {
  return dualstack[tos2-1];
}

bool DualStack::empty1() {
	return (tos1 == 0);
}

bool DualStack::empty2() {
	return (tos2 == (size - 1));
}

// Test the dualstack class. Convert an infix expression to postfix 
// and than evaluate the postfix expression. Operators ar pushed on
// the second stack and numbers on the first stack.
int testDualStack(const char* infix) {
	
  DualStack ds = DualStack(strlen(infix));
  const char* iptr = infix;
  int n1, n2 = 0;

  while (*iptr != 0) {
    //Push operators on the second stack
    if (*iptr == '+' || *iptr == '-' || *iptr == '*' || *iptr == '/') {
      ds.push2(*iptr++);
      continue;
    }

    //Push numbers on the first stack
    if (*iptr >= '0' && *iptr <= '9')
      {
	ds.push1(0);
	while (*iptr >= '0' && *iptr <= '9') {
	  n1 = ds.top1();
	  ds.pop1();
	  ds.push1((n1 * 10) + *iptr++ - '0');
	}
	continue;
      }

    if (*iptr == ')') {
      n1 = ds.top1();
      ds.pop1();
      n2 = ds.top1();
      ds.pop1();
      switch (ds.top2()) {
      case '+':
	ds.push1(n1 + n2);
	break;
      case '-':
	ds.push1(n2 - n1);
	break;
      case '*':
	ds.push1(n1*n2);
	break;
      case '/':
	ds.push1(n2 / n1);//throw exception division by 0
	break;
      }
      ds.pop2();
      iptr++;
      continue;
    }
    iptr++;
  }

  while (!ds.empty2()) {
    n1 = ds.top1();
    ds.pop1();
    n2 = ds.top1();
    ds.pop1();
    switch (ds.top2()) {
    case '+':
      ds.push1(n1 + n2);
      break;
    case '-':
      ds.push1(n2 - n1);
      break;
    case '*':
      ds.push1(n1*n2);
      break;
    case '/':
      ds.push1(n2 / n1);//throw exception division by 0
      break;
    }
    ds.pop2();
  }

  return ds.top1();
}
