#include "polyList.h"
#include <cmath>

//build coef * x ^ deg
PolyList::PolyList(Number coef, int deg) {
  poly = new Node(coef, deg);
}

PolyList::PolyList(const PolyList& pl) {
  poly = new Node (pl.poly->coef, pl.poly->exp);
  link n = poly;
  for (link t = pl.poly->next; t != 0; t=t->next) {
    n->next = new Node (t->coef, t->exp);
  }
}

PolyList::~PolyList() {
  while(poly != 0) {
    link t = poly;
    poly = poly->next;
    delete t;
  }
}

// Use Horner algorithm i.e.:
// ax^3 + bx^2 + cx + d =
// ((ax +b)x +c)x + d
Number PolyList::evaluate(Number x) const {
  Number start_gap = 1; //take into account first null coefficients
  if (poly->exp > 0) start_gap = pow(x, poly->exp - 1);
  return evalFactor(poly, x, start_gap);
}

Number PolyList::evalFactor(link p, Number x, int start_gap) const {
 if (p) {
   Number gap = 1; //take into account null coefficients
   Number next_start_gap = 1; 
   if (p->next) {
     gap = pow(x, p->next->exp - p->exp - 1);
     next_start_gap = pow(x, p->next->exp - 1);
   }
   return p->coef * x * gap * start_gap + evalFactor(p->next, x, next_start_gap);
 }
 else return 0;
}

PolyList& PolyList::operator=(const PolyList& rhs) {
  if (&rhs != this) {
    //delete current polynomial
    while(poly != 0) {
    link t = poly;
    poly = poly->next;
    delete t;
    }
    //copy rhs
    poly = new Node (rhs.poly->coef, rhs.poly->exp);
    link n = poly;
    for (link t = rhs.poly->next; t != 0; t=t->next) {
      n->next = new Node (t->coef, t->exp);
    }   
  }
  return *this;
}

const PolyList operator+(const PolyList& lhs, const PolyList& rhs) {

  PolyList sum (0, 0); //sentinel
  PolyList::link n = sum.poly;

  //copy the left list in the new one
  for (PolyList::link l = lhs.poly; l!=0; l=l->next) { 
    n->next = new PolyList::Node (l->coef, l->exp);
    n = n->next; 
  }
  //copy the right list in the new one
  for (PolyList::link r = rhs.poly; r != 0; r = r->next) { 
    for (n = sum.poly; n != 0; n = n->next) {
      //sum coefficient if a node with the same exp already exists
      if (n->next != 0 && n->next->exp == r->exp) { 
	n->next->coef += r->coef;
	break;
      }
      //create a new node otherwise
      if(n->next == 0 || n->next->exp > r->exp) {
	PolyList::link t = n->next;
	n->next = new PolyList::Node (r->coef, r->exp);
	n->next->next = t;
	break;
      }
    }
  }
  sum.poly = sum.poly->next;
  return sum;
}

const PolyList operator*(const PolyList& lhs, const PolyList& rhs) {
  PolyList mul (0,0); //sentinel
  for (PolyList::link l = lhs.poly; l != 0; l = l->next) {
    for (PolyList::link r = rhs.poly; r != 0; r = r->next) {
      for (PolyList::link n = mul.poly; n!=0; n=n->next) {
	int new_exp = l->exp + r-> exp; 
	//sum coefficients product if a node with the new exp already exists
	if (n->next != 0 && n->next->exp == new_exp) {
	  n->next->coef += (l->coef * r->coef);
	  break;
	}
	//create a new node otherwise
	if (n->next == 0 || n->next->exp > new_exp) {
	  PolyList::link t = n->next;
	  n->next = new PolyList::Node ((l->coef * r->coef), new_exp);
	  n->next->next = t;
	  break;
	}
      }
    }
  }
  mul.poly = mul.poly->next;
  return mul;
}

std::ostream& operator<<(std::ostream& out, const PolyList rhs) {
  for(PolyList::link t = rhs.poly; t != 0; t = t->next) {
    out << std::showpos <<  t->coef << "x^" << t->exp << " ";
  }
  out << std::endl;
  return out;
}

void testPolyList(void) {
  PolyList a(3, 4);
  PolyList b(2, 3);
  std::cout << a;
  std::cout << b;
  PolyList c = a + b;
  std::cout << c;
  PolyList d = a*c;
  std::cout << d;
  std::cout << c.evaluate(2);
}
