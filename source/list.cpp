#include "list.h"
#include <cstdlib> //rand

List::List(int n) {
  srand(time(0));
  head = new Node(rand()%1000,0);
  link t = head;
  for(int i = 1; i < n; ++i) {
    t->next = new Node(rand()%1000,0);
    t = t->next;
  }
}

List::~List() {
  while(head != 0) {
    link r = head;
    head = head->next;
    delete r;
  }
  head = 0;
}

List::List(const List& ml) {
  head = new Node( ml.head->item, 0);
  link newList = head;
  for(link t = ml.head->next; t!=0; t=t->next) {
    newList->next = new Node(t->item,0);
    newList = newList->next;
  }
}

void List::removeEven(void) {
  link t = head;
  while(t != 0) {
    link r = t->next;
    if(r == 0) break;
    t->next = r->next;
    t=t->next;
    delete r;
  }
}

int oddTest(List::link t) {
  std::cout << t->item << " ppp " <<  (t->item) % 2 <<std::endl ;
  return (t->item) % 2;
}

void List::modify(isOdd) {
    Node fakeHead(0,head);
    link t = &fakeHead;
    while(t->next != 0) {
        if(t->next->item % 2) {
            link r = t->next;
            t->next = r->next;
            delete r;
        }
        else{
            t = t->next;
        }
    }
    head = fakeHead.next;
}

void List::reverse(void) {
  link r = 0; //ptr to already reversed node
  link nr = head; //ptr to node to be reversed
  while(nr != 0) {
    link t = nr->next;
    nr->next = r;
    r = nr;
    nr = t;
  }
  head = r;
}

List::link List::get (void) {
  return head;
}

void List::set (link t) {
  head = t;
}

void reverseRec(List& nr) {
  static List::link r = 0;

  if (!nr.head) {
    nr.head = r;
    return;
  }

  List::link t = nr.head->next;
  nr.head->next = r;
  r = nr.head;
  nr.head = t;
  reverseRec(nr);  
}

void removeLastRec (List::link t) {
  if (t->next->next == 0) {
    delete t->next;
    t->next = 0;
    return;
  }
  removeLastRec(t->next);
}

Item max(List::link t) {
  if (t->next == 0) return t->item;
  Item r = max (t->next);
  return (t->item > r) ? t->item : r;
}

void List::biggestBack(void) {
  link biggest = head;
  link preBiggest = 0;
  link t = head;
  int i = 0;
  
  for(t = head; t->next != 0; t = t->next) {
    std::cout << i++ << " ";
    if(t->next->item > biggest->item) {
      biggest = t->next;
      preBiggest = t;
    }
  }
  t->next = biggest;
  preBiggest->next = biggest->next;
  biggest->next = 0;
}

void List::rearrangeOddEven(void) {
  
  link even = head->next;
  link odd = head;
  link evenHead =even;
  int cnt = 1;
  for(link t = even->next; t !=0; t = t->next) {
    if(cnt%2 == 0){
      even->next = t;
      even = even->next;
    }
    else {
      odd->next = t;
      odd = odd->next;
    }
    ++cnt;
  }
  even->next = 0;
  odd->next = evenHead;
}

void List::sort(void) {
  Node fakeHeadOld(0, 0);
  fakeHeadOld.next = head;
  Node fakeHeadNew(0, 0);
  link u, n;
  for(link t = fakeHeadOld.next; t != 0; t = u) {
    u = t->next;
    for(n = &fakeHeadNew; n->next != 0; n = n->next) {
      if (n->next->item > t->item) break;    
    }
    t->next = n->next;//append to the current node the new list
    n->next = t;//insert current node inthe right place 
  }
  head = fakeHeadNew.next;
}

std::ostream& operator<<(std::ostream& out, const List& ml) {
  List::link t = ml.head;
  do {
    out << t->item << " ";
    t = t->next;
  }
  while(t!=0);

  return out;
}


CircularList::CircularList(int size) {
  n = new Node(1,0);
  n->next = n;
  link t = n;
  for(int i = 2; i <= size; ++i) {
    t->next = new Node(i,n);
    t = t->next;
  }
}

int CircularList::size(void) {
  int cnt = 1;
  for(link t = n->next; t!=n; t = t->next) ++cnt;
  return cnt;
  
}

CircularList::link CircularList::getNode(int p) {
  link t = n;
  for(int i = 1; i < p; ++i) t = t->next;
  return t;
  
}

void CircularList::moveNode(link t, link x) {
  link start = t->next; //node to be moved
  t->next = start->next; //removed node to be moved
  link dest = x->next->next;//node preceeding where to insert
  start->next = dest->next;
  dest->next = start;

}


Item CircularList::selectLeader(int m) {

  link t = n;
  while(t != t->next) {
    for(int i = 1; i < m; ++i) {
      t = t->next;
    }
    link r = t->next;
    t->next = t->next->next;
    std::cout <<  " Del " << r->item << std::endl;
    delete r;
  }
  n = t;
  return t->item;
}

CircularList::~CircularList() {

  while(n != n->next) {
    link t = n->next;
    n->next = t->next;
    std::cout << "Del " << t->item << std::endl;
    delete t;
  }
  
  std::cout << "Del " << n->item << std::endl;
  delete n;
  n = 0;
}

ListArray::ListArray(int n) {
  item = new Item[n];
  next = new int[n];
  for(int i = 0; i < n; ++i) {
    item[i] = i+1;
    next[i] = i+1;
  }
  next[n-1] = 0;
}

std::ostream& operator<<(std::ostream& out, const CircularList& mcl) {
  CircularList::link  tmp = mcl.n;

  do {
    out << tmp->item << " ";
    tmp = tmp->next;
  }while(tmp != mcl.n);
  out << std::endl;
  return out;
}


Item ListArray::selectLeader(int m) {
  int x = 8;
  std::cout <<  next[x] << next[next[x]] <<  std::endl;
  while(next[x]!=next[next[x]]) {
    for(int i = 0; i < m-1; ++i) {
      x = next[x];
      std::cout << i <<  " " << x << std::endl;
    }
    std::cout << x <<  " Del " << item[next[x]] << std::endl;
    next[x] = next[next[x]];
  }
  return item[next[x]];
}
