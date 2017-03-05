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

   Link merge (Link l, Link r);
   Link mergesort(Link l);
   
 public:
   List(){head = 0;};
   ~List();
   List(const List& l);
   void quicksort (void);
   void mergesort (void);
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

// The main function for quick sort, just a wrapper
// over recursive function quickSortRec()
template <class Item>
void List<Item>::quicksort (void) {
  Link tail = head;
  while (tail->next != 0) tail = tail->next;
  quicksortRec(head, tail);
}

// Implement the sorting for the element between
// its argument
template <class Item>
void List<Item>::quicksortRec(Link& headRec, Link& tailRec) {

  //base condition
  if (!headRec || headRec == tailRec) return;
  //partition the list updating head and tail
  Link v = partition(headRec, tailRec);

  //if pivot is the smallest there is no need
  //of recursion on the left side
  if (headRec != v) {
    Link t = headRec;
    //find the node before the pivot
    while (t->next != v) t = t->next;  
    quicksortRec(headRec, t);
  }
  //if pivot is the biggest there is no need
  //of recursion on the right side
  if (v!= tailRec) quicksortRec(v->next, tailRec);
}

// Partitions the list taking the last element as the pivot
// During partition, both the head and end of the list might change
// so the corresponding arguments are references
// return a pointer to the pivot
template <class Item>
typename List<Item>::Link List<Item>::partition(Link& headRec, Link& tailRec) {
	
  Link t = headRec;     //current node
  Link v = tailRec;     //pivot node
  Link last = v->next;  
  Link newHead, newTail;
  newHead = newTail = v;

  while (t != v) {
    Link next = t->next;
    if (t->item < v->item) {
      //update head if current node
      //is lower than pivot
      t->next = newHead;
      newHead = t;
    }
    else {
      //update tail if current node
      //is bigger than pivot
      newTail->next = t;
      newTail = newTail->next;
    }
    t = next;
  }
  newTail->next = last;
  headRec = newHead;
  tailRec = newTail;
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

//merge implementation for linked list
template <class Item>
typename List<Item>::Link List<Item>::merge(Link l, Link r) {
  Node mergedHead(0);
  Link merged = &mergedHead;
  while (l && r) {
    if (l->item > r->item) {
      merged->next = r;
      r = r->next;
    }
    else {
      merged->next = l;
      l = l->next;
    }
    merged = merged->next;
  }
  if (!l) merged->next = r;
  else    merged->next = l;
  return mergedHead.next;
}

//merge implementation for linked list
template <class Item>
typename List<Item>::Link List<Item>::mergesort(Link list) {

  if (!list->next || !list) return list;
  
  Link l, r;
  l = list;
  r = list->next;//r = list fails when list has two nodes
  
  while (r != 0 && r->next != 0) {
    l = l->next;
    r = r->next->next;
  }
  r = l->next;
  l->next = 0;
  l = list;
  l = mergesort(l);
  r = mergesort(r);
 return merge(l,r);
  
}

//merge implementation for linked list
template <class Item>
void List<Item>::mergesort(void) {
  head = mergesort(head);
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
