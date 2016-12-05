#include "complexNumbers.h"

std::ostream& operator<<(std::ostream& out, const ComplexNumbers& cn) {
  out << cn.real << std::showpos << cn.img << "i";
  return out;
}

//return value is const so that it can be used as temporary and cannot be
//modified as lvalue; function is const because a new value is created without
//modifying the existing ones
const ComplexNumbers ComplexNumbers::operator+(const ComplexNumbers& cn) const {
  return ComplexNumbers(real + cn.real, img + cn.img);
}

ComplexNumbers& ComplexNumbers::operator+=(const ComplexNumbers& cn) {
  real += cn.real;
  img  += cn.img;
  return *this;
}
