#include "doubleQueue.h"
#include <cstdlib>

//common to DoubleQueue base abstract class
void DoubleQueue::error(const char* err) const {
	std::cout << err << std::endl;
}

std::ostream& operator<<(std::ostream& out, const DoubleQueue& dq) {
  dq.dump(out);
  return out;
}

//DoubleQueue implementation with array
DoubleQueueArray::DoubleQueueArray(int sz) {
  size = sz+1;
  head = tail = 0;
  dq = new Item[size];
}

DoubleQueueArray::~DoubleQueueArray() {
  delete[] dq;
  size = head = tail = 0;
}

void DoubleQueueArray::putFront(Item x) {
  int tmp_head = (head - 1 + size) % size;
  if (tmp_head == tail) {
    error("Queue full!");
    exit(EXIT_FAILURE);
  }
  else {
    head = tmp_head;
    dq[head] = x;
  }
}

Item DoubleQueueArray::getFront(void) {
  if (head == tail) {
    error("Queue empty!");
    exit(EXIT_FAILURE);
  }
  else {
    Item x = dq[head];
    head = (head + 1) % size;
    return x;
  }
}

void DoubleQueueArray::putBack(Item x) {
  int tmp_tail = (tail + 1) % size;
  if (tmp_tail == head) {
     error("Queue full!");
     exit(EXIT_FAILURE);
  }
  else {
    dq[tail] = x;
    tail = tmp_tail;
  }
}

Item DoubleQueueArray::getBack(void) {
   if (head == tail) {
    error("Queue empty!");
    exit(EXIT_FAILURE);
  }
  else {
    tail = (tail -  1 + size) % size;
    return dq[tail];
  }
}

void DoubleQueueArray::dump(std::ostream& out) const {
  int i = head;
  while(i != tail) {
     out << dq[i] << " ";
     i = (i+1)%size;
  }
  out << std::endl;
}

DoubleQueueList::DoubleQueueList() {
  head = tail = 0;
}

DoubleQueueList::~DoubleQueueList() {
  while (head != 0) {
    link t = head;
    head = t->next;
    head->prev = 0;
    delete t;
  }
}

void DoubleQueueList::putFront(Item x) {
  link t = new DoubleNode(x, head, 0);
  if (!t) {
    error("Queue full!");
    exit(EXIT_FAILURE);
  }
  else { 
    if (!head) { //empty queue
      head = tail = t;
    }
    else {
      head->prev = t;
      head = t;
    }
  }
}

Item DoubleQueueList::getFront(void) {
  if (!head) {
    error("Queue empty!");
    exit(EXIT_FAILURE);
  }
  else {
    link t = head;
    if (tail != head) {
      head = t->next;
      head->prev = 0;
    }
    else { //one element queue
      head = tail = 0;
    }
    Item x = t->item;
    delete t;
    return x;
  }
}

void DoubleQueueList::putBack(Item x) {
  link t = new DoubleNode(x, 0, tail);
  if (!t) {
    error("Queue full!");
    exit(EXIT_FAILURE);
  }
  else {
    if (!tail) {//empty queue
      tail = head = t;
    }
    else {
      tail->next = t;
      tail = t;
    }
  }
}

Item DoubleQueueList::getBack(void) {
  if (!tail) {
    error("Queue empty!");
    exit(EXIT_FAILURE);
  }
  else {
    link t = tail;
    if (head != tail) {
      tail = t->prev;
      tail->next = 0;
    }
    else {//one element queue
      head = tail = 0;
    }
    Item x = t->item;
    delete t;
    return x;
  }
}

void DoubleQueueList::dump(std::ostream& out) const {
  for (link t = head; t != 0; t = t->next) {
    out << t->item << " ";
  }
  out << std::endl;
}

void testDoubleQueue(DoubleQueue* dq, const char* commands) {
  const char* cmd = commands;
  while(*cmd != 0) {

    if (*cmd == '+') {
      dq->getFront();
    }

    if (*cmd == '*') {
      dq->getBack();
    }

    if (isupper(*cmd)) {
      dq->putFront(*cmd);
    }

    if (islower(*cmd)) {
      dq->putBack(*cmd);
    }

    std::cout << *dq;
    cmd++;
  }
}
