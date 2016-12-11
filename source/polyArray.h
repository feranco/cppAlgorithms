#ifndef POLYARRAY_H
#define POLYARRAY_H

#include <iostream>

typedef double Number; 

class PolyArray {
  Number* poly;
  int size;
 public:
  PolyArray (Number coef, int exp);
  ~PolyArray ();
  PolyArray (const PolyArray& rhs);
  PolyArray& operator= (const PolyArray& rhs);
  Number evaluate (Number x) const;
  const PolyArray& operator+= (const PolyArray& rhs);
  const PolyArray& operator*= (const PolyArray& rhs);
  friend const PolyArray operator+ (const PolyArray& lhs, const PolyArray& rhs);
  friend const PolyArray operator* (const PolyArray& lhs, const PolyArray& rhs);
  friend std::ostream& operator<< (std::ostream& out, const PolyArray& rhs);
};


#endif
