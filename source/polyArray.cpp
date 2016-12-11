#include "polyArray.h"

PolyArray::PolyArray (Number coef, int exp) {
  size = exp + 1;
  poly = new Number[size];
  for (int i = 0; i < size-1; ++i) {
    poly[i] = 0;
  }
  poly[size-1] = coef;
}

PolyArray::~PolyArray() {
  delete[] poly;
}

PolyArray::PolyArray (const PolyArray& rhs) {
  size = rhs.size;
  poly = new Number[size];
}

PolyArray& PolyArray::operator= (const PolyArray& rhs) {
  if(&rhs != this) {
    delete[] poly;
    size = rhs.size;
    poly = new Number[size];
    for (int i = 0; i < size; ++i) {
      poly[i] = rhs.poly[i];
    }
  }
  return *this;
}

Number PolyArray::evaluate (Number x) const {
  Number r = 0;
  for (int i = size-1; i >= 0; i--) {
    r = r*x + poly[i];
  }
  return r;
}

const PolyArray& PolyArray::operator+= (const PolyArray& rhs) {

  if (rhs.size > size) {
    Number* n = new Number[rhs.size];
    for (int i = 0; i < size; ++i) {
      n[i] += poly[i];
    }
    for (int i = size; i < rhs.size; ++i) {
      n[i] = 0;
    }
    delete[] poly;
    size = rhs.size;
    poly = n;
  }
  
  for (int i = 0; i < size; ++i) {
    poly[i] += rhs.poly[i];
  }
  return *this;
}

const PolyArray& PolyArray::operator*= (const PolyArray& rhs) {
  Number* n = new Number[size + rhs.size];

  for (int i = 0; i < (size + rhs.size); ++i) n[i] = 0;
  
  for (int i = 0; i < size; ++i) {  
    for (int j = 0; i < rhs.size; ++i) {
      n[i+j] +=  poly[i] * rhs.poly[j];
    }
  }

  delete[] poly;
  poly = n;
  size += rhs.size;
  
  return *this;
}

const PolyArray operator+ (const PolyArray& lhs, const PolyArray& rhs) {
  PolyArray n(0, (lhs.size >= rhs.size ? lhs.size-1 : rhs.size-1));
  
  for (int i = 0; i < lhs.size; ++i) {
    n.poly[i] += lhs.poly[i];
  }
  
  for (int i = 0; i < rhs.size; ++i) {
    n.poly[i] += rhs.poly[i];
  }
  return n;
}

const PolyArray operator* (const PolyArray& lhs, const PolyArray& rhs) {
  PolyArray n(0, lhs.size + rhs.size);
  
  for (int i = 0; i < lhs.size; ++i) {  
    for (int j = 0; i < rhs.size; ++i) {
      n.poly[i+j] +=  lhs.poly[i] * rhs.poly[j];
    }
  }
  return n;
}

std::ostream& operator<< (std::ostream& out, const PolyArray& rhs) {
  for (int i = 0; i < rhs.size; ++i) {
    if (rhs.poly[i] != 0) {
      std::cout << ((rhs.poly[i] > 0) ? "+" : "-") << rhs.poly[i] << "x^" << i << " ";
    }
  }
  std::cout << std::endl;
  return out;
}
