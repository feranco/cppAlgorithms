#ifndef LIST_H
#define LIST_H
#include <iostream>

template <class Item>
class List;

template <class Item>
std::ostream& operator<<(std::ostream& out, const List<Item>& rhs);


template <class Item>
class List {
   struct Node {
     Item  item;
     Node* next;
     Node(Item i) {item = i; next = 0;}
     Node(Item i, Node* n) {item = i; next = n;}
   };

   typedef Node* Link;
   Link head;
   void quicksortRec (Link& headRec, Link& tailRec);
   Link partition (Link& headRec, Link& tailRec);
   
 public:
   List(){head = 0;};
   ~List();
   List(const List& l);
   void quicksort (void);
   void insertInFront (Item item);
   friend std::ostream& operator<< <> (std::ostream& out, const List& rhs);
};

template <class Item>
List<Item>::~List() {
  while(head != 0) {
    Link t = head;
    head = head->next;
    delete t;
  }
  head = 0;
}

template <class Item>
List<Item>::List(const List& ml) {
  head = new Node( ml.head->item, 0);
  Link newList = head;
  for(Link t = ml.head->next; t!=0; t=t->next) {
    newList->next = new Node(t->item,0);
    newList = newList->next;
  }
}

template <class Item>
void List<Item>::insertInFront (Item item) {
  Link tmp = new Node(item, head);
  head = tmp;
}

template <class Item>
void List<Item>::quicksort (void) {
  Link tail = head;
  while (tail->next != 0) tail = tail->next;
  quicksortRec(head, tail);
}

template <class Item>
void List<Item>::quicksortRec (Link& headRec, Link& tailRec) {
  if (headRec == tailRec) return;
  Link v = partition(headRec, tailRec);
  Link prev = headRec;
  while (prev->next != v) prev = prev->next;
  quicksortRec (headRec, prev);
  quicksortRec (v->next, tailRec);
}

template <class Item>
typename List<Item>::Link List<Item>::partition (Link& headRec, Link& tailRec) {
  Node NodeA(0,0);
  Node NodeB(0,0);
  Link left = &NodeA;
  Link right = &NodeB;
  Link v = tailRec;
 
  for (Link t = headRec; t != tailRec; t = t->next) {
    if (t->item < v->item) {
      left->next = t;
      left = left->next;
    }
    else {
      right->next = t;
      right = right->next;
    }
  }
  left->next = v;
  right->next = v->next;
  v->next =  NodeB.next;
  headRec = NodeA.next;
  tailRec = right;
  return v;
}


template <class Item>
std::ostream& operator<<(std::ostream& out, const List<Item>& rhs) {
  typename List<Item>::Link t = rhs.head;
  do {
    out << t->item << " ";
    t = t->next;
  }
  while(t!=0);

  return out;
}

#if 0
typedef int Item;
 
class List {
   //Node definition
   struct Node {
     Item  item;
     Node* next;
     Node(Item i, Node* n) {item = i; next = n;}
   };

   typedef Node* link;
   typedef int (*isOdd)(link);
   link head;
   
 public:
   List(int n);
   ~List();
   List(const List& l);
   friend std::ostream& operator<<(std::ostream& out, const List& rhs);
   void biggestBack(void);
   void rearrangeOddEven(void);
   void modify(isOdd);
   void reverse(void);
   void sort(void);
   void removeEven(void);
   link get (void);
   void set (link t);
   friend void removeLastRec(link t);
   friend void reverseRec(List& nr);
   friend Item max(link t);
   friend int oddTest(link t);
 };

int oddTest(List::link t);

class CircularList {
  
  //Node definition
  struct Node {
    Item  item;
    Node* next;
    Node(Item i, Node* n) {item = i; next = n;}
  };

  typedef Node* link;
  link n;
 public:
  
  CircularList(int size);
  ~CircularList();
  int size(void);
  link getNode(int i);
  void moveNode(link t, link x);
  Item selectLeader(int m);
  friend std::ostream& operator<<(std::ostream& out, const CircularList& rhs);  
 };




class ListArray {
  Item* item;
  int*  next;
  public:
  ListArray(int n);
  Item selectLeader(int m);
  ~ListArray();
  
};
#endif
#endif
