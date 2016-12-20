#ifndef LIST_H
#define LIST_H
#include <iostream>

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
