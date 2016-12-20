#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

class Array{
  int size;
  bool* isPrime;
  int*  a;
  
 public:
  Array(int size);
  ~Array();
  int eratosthenesSieve(bool printPrime = false);
  int max (int idx = 0);
  friend std::ostream& operator<<(std::ostream& out, const Array& rhs);
};

void testIsPrime(int size);
void testPrimeStat(void);
bool isHead(int probability = 2);
void coinFlipSimulation(int nExp, int  nFlip);

#endif
