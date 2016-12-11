#ifndef POLYLIST_H
#define POLYLIST_H

#include <iostream>

typedef double Number;

//linked list implementation of polynomial
class PolyList {
  struct Node {
    Number coef;
    int exp;
    Node* next;
    Node(Number c, int e) {coef = c; exp = e; next = 0;};
  };

  typedef Node* link;
  link poly; 
  Number evalFactor(link p, Number x, int start_gap) const;
 public:
  PolyList(Number coef, int deg);
  PolyList(const PolyList& pl);
  ~PolyList();
  Number evaluate(Number x) const;
  PolyList& operator=(const PolyList& rhs);
  friend std::ostream& operator<<(std::ostream& out, const PolyList rhs);
  friend const PolyList operator+(const PolyList& lhs, const PolyList& rhs);
  friend const PolyList operator*(const PolyList& lhs, const PolyList& rhs);
};

void testPolyList(void);

#endif
