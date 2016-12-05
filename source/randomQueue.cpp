#include "randomQueue.h"
#include <cstdlib>

const int random_queue_size = 5;

//Random Queue Implementation with array

RandomQueueArray::RandomQueueArray(int sz) {
  size = sz;
  tail = 0;
  rq = new Item[size];
  srand(time(0));
}

RandomQueueArray::~RandomQueueArray() {
  delete[] rq;
  size = tail = 0;
}

void RandomQueueArray::put(Item x) {
  if (tail < size) {
    rq[tail++] = x;
  }
  else {
    error("Queue Full!");
    exit(EXIT_FAILURE);
  }
}

void RandomQueueArray::putIgnoreNew(Item x) {
  bool is_existing = false;
  for (int i = 0; i < tail; ++i) {
    if (rq[i] == x) {
      is_existing = true;
      break;
    }
  }

  if (!is_existing) {
  
    if (tail < size) {
      rq[tail++] = x;
    }
    else {
      error("Queue Full!");
      exit(EXIT_FAILURE);
    }

  }
}

void RandomQueueArray::putForgetOld(Item x) {
  
  bool is_existing = false;
  int old_idx;
  
  for (int i = 0; i < tail; ++i) {
    if (rq[i] == x) {
      is_existing = true;
      old_idx = i;
      break;
    }
  }

  if(is_existing) {
    tail--;
    for (int i = old_idx; i < tail; ++i) {
      rq[i] = rq[i+1];
    }
  }
  
  if (tail < size) {
    rq[tail++] = x;
  }
  else {
    error("Queue Full!");
    exit(EXIT_FAILURE);
  }
}

Item RandomQueueArray::get(void) {
  if (tail > 0) {
    int getIdx = rand() % tail;
    Item getItem = rq[getIdx];
    rq[getIdx] = rq[--tail];
    return getItem;
  }
  else {
    error("Queue Empty!");
    exit(EXIT_FAILURE);
  }
}

void RandomQueueArray::dump(std::ostream& out) const {
  for (int i = 0; i < tail; i++) {
    out << rq[i] << " ";
  }
  out << std::endl;
}

RandomQueueList::RandomQueueList() {
  head = 0;
  size = 0;
}

RandomQueueList::~RandomQueueList() {
  while (head!=0) {
    link t = head;
    head = t->next;
    delete t;
  }
}

void RandomQueueList::put(Item x) {
  link t = new Node(x, head->next);
  if (t) {
    head->next = t;
    size++;
  }
  else {
    error("Queue Full!");
    exit(EXIT_FAILURE);
  }
}

void RandomQueueList::putIgnoreNew(Item x) {
  link t = new Node(x, head->next);
  if (t) {
    head->next = t;
    size++;
  }
  else {
    error("Queue Full!");
    exit(EXIT_FAILURE);
  }
}


void RandomQueueList::putForgetOld(Item x) {
  link t = new Node(x, head->next);
  if (t) {
    head->next = t;
    size++;
  }
  else {
    error("Queue Full!");
    exit(EXIT_FAILURE);
  }
}

Item RandomQueueList::get() {
  if (size > 0) {
    int idx = rand() % size;
    link t = head;

    for (int i = 0; i < idx; ++i) {
      t = t->next;
    }
    link r = t->next;
    Item x = r->item;
    t->next = r->next;
    delete r;
    size--;
    return x;
  }
  else {
    error("Queue Empty!");
    exit(EXIT_FAILURE);
  }
}

void testRandomQueue(MyQueue* q, int n) {
   Item* samples = new Item[n];
   for (int i = 0; i < random_queue_size; ++i) {
	   q->put(i+1);
   }

   std::cout << "Extract " << n << " numbers for lottery: " << std::endl;
   for (int i = 0; i < n; ++i) {
	   samples[i] = q->get();
	   std::cout << samples[i] << std::endl;
	   std::cout << *q;
   }
   std::cout << std::endl;
}

void RandomQueueList::dump(std::ostream& out) const {
   for (link t = head->next; t != 0; t = t->next) {
	   out << t->item << " ";
   }
   out << std::endl;
}

Item RandomQueueList::getReservoirSample(void) {
   link r = head; //node before the one to be deleted
   int seen = 2; //number of already seen nodes
   for (link t = r; t->next != 0; t = t->next, seen++) {
	   if (rand() % seen == 0) r = t->next; 
   }
   link d = r->next;
   Item x = d->item;
   r->next = d->next;
   delete d;
   return x;
}
