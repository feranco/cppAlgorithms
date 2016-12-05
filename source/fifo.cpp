#include "fifo.h"
#include <cstdlib>

//FIFO implementation with linked list
FIFOList::FIFOList() {
  head = tail = 0;
}

FIFOList::~FIFOList() {
  while(head!= 0) {
    link t = head;
    head = t->next;
    delete t;
  }
  head = tail = 0;
}

void FIFOList::put(Item x) {
  link t = new Node(x);

  if(t) {
    if(head == 0) {
      head = tail = t;
    }
    else {
      tail->next = t;
      tail = t;
    }
  }
  else {
    error("FIFO full!");
    exit(EXIT_FAILURE);
  }
}


void FIFOList::putIgnoreNew(Item x) {
  bool is_existing = false;
  for(link t = head; t!=0; t=t->next) {
    if(t->item == x) {
      is_existing = true;
      break;
    }
  }

  if(!is_existing) {  
    link t = new Node(x);

    if(t) {
      if(head == 0) {
	head = tail = t;
      }
      else {
	tail->next = t;
	tail = t;
      }
    }
    else {
      error("FIFO full!");
      exit(EXIT_FAILURE);
    }
  }
}

void FIFOList::putForgetOld(Item x) {
  Node fakeHead(0);
  fakeHead.next = head;
  for(link t = &fakeHead; t->next!=0; t=t->next) {
    if(t->next->item == x) {
     link r = t->next;
     t->next = r->next;
     delete r;
     break;
    }
  }

  link t = new Node(x);

  if(t) {
    if(head == 0) {
      head = tail = t;
    }
    else {
      tail->next = t;
      tail = t;
    }
  }
  else {
    error("FIFO full!");
    exit(EXIT_FAILURE);
  }
  
}

Item FIFOList::get(void) {
  if(head) {
    Item x = head->item;
    link t = head;
    head = t->next;
    delete t;
    return x;
  }
  else {
    error("FIFO empty!");
    exit(EXIT_FAILURE);
  }
}

void FIFOList::dump(std::ostream& out) const {
  for(link t = head; t!=0; t=t->next) {
    out << t->item << " ";
  }
  out << std::endl;

}

// FIFO implementation with array
FIFOArray::FIFOArray(int sz) {
  size = sz+1;
  fifo = new Item[size];
  head = tail = 0;
}

FIFOArray:: ~FIFOArray() {
  delete[] fifo;
}

void FIFOArray::put(Item x) {
  if ((tail + 1) % size == head) {
    error("FIFO full!");
    exit(EXIT_FAILURE);
  }
  else {
    fifo[tail++] = x;
    tail = tail % size;
  }
}

void FIFOArray::putIgnoreNew(Item x) {
  bool is_existing = false;
  for (int i = head; i!=tail; ++i) {
    if (i==size) i = 0;
    if (fifo[i]==x) {
      is_existing = true;
      break;
    }
  }

  if (is_existing) {   
    if ((tail + 1) % size == head) {
      error("FIFO full!");
      exit(EXIT_FAILURE);
    }
    else {
      fifo[tail++] = x;
      tail = tail % size;
    }
  }
}

void FIFOArray::putForgetOld(Item x) {
  bool is_existing = false;
  int old_idx;
  
  //check if x is already existing
  for (int i = head; i != tail; ++i) {
    if (i == size) i = 0;
    if (fifo[i] == x) {
      is_existing = true;
      old_idx = i;
      break;
    }
  }

  if (is_existing) {
    tail = tail - 1 + size % size;
    for (int i = old_idx; i!=tail; ++i) {
      if (i == size) i = 0;
      fifo[i] = fifo[(i + 1) % size];
    }
  }

  if ((tail + 1) % size == head) {
    error("FIFO full!");
    exit(EXIT_FAILURE);
  }
  else {
    fifo[tail++] = x;
    tail = tail % size;
  }
}


Item FIFOArray::get(void) {
  if (head == tail) {
    error("FIFO empty!");
    exit(EXIT_FAILURE);
  }
  else {
    head = head % size;
    return fifo[head++];
  }
}

void FIFOArray::dump(std::ostream& out) const {
 for (int i = head; i!=tail; i++) {
    if (i == size) i = 0;
    out << fifo[i] << " ";
  }
  out << std::endl;
}

FIFOArray::FIFOArray(const FIFOArray& fa) {
  size = fa.size;
  head = fa.head;
  tail = fa.tail;
  fifo = new Item[size];
  for (int i = 0; i < size; ++i) fifo[i] = fa.fifo[i];
}

FIFOArray& FIFOArray::operator=(const FIFOArray& fa) {
  if(&fa != this) {
    delete[] fifo;
    size = fa.size;
    head = fa.head;
    tail = fa.tail;
    fifo = new Item[size];
    for (int i = 0; i < size; ++i) fifo[i] = fa.fifo[i];
  }
  return *this;
}
