#ifndef COMPLEX_NUMBERS_H
#define  COMPLEX_NUMBERS_H

#include <iostream>

class ComplexNumbers {
  float real;
  float img;
 public:
  ComplexNumbers(float r, float i) {real = r; img = i;};
  ~ComplexNumbers();
  void  setReal(float r) {real = r;};
  void  setImg(float i) {img = i;};
  float getReal(void) const {return real;};
  float getImg(void) const {return img;};
  const ComplexNumbers operator+(const ComplexNumbers& r) const;
  ComplexNumbers& operator+=(const ComplexNumbers& cn);
  friend std::ostream& operator<<(std::ostream& out, const ComplexNumbers& cn);
};
#endif
