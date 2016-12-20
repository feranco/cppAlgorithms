#include "array.h"
#include <iostream>
#include <cstdlib> //rand
#include <fstream>

Array::Array(int size) {
  if(size > 0) {
    srand(time(NULL));
    isPrime = new bool[size];
    a = new int[size];
    this->size = size;

    for (int i=0; i<size-1; ++i) {
      a[i] = rand() % 100;
    }
  }
}

Array::~Array() {
  delete[] isPrime;
}

int Array::eratosthenesSieve(bool printPrime) {

  int cntPrime = 0;

  for(int i = 0; i < size; ++i) {
    isPrime[i] = true;
  }

  for(int i = 2; i < size; ++i) {
    if(isPrime[i]) {
      cntPrime++;
      for(int j = i; i*j < size; ++j) {
	isPrime[i*j] = false;
      }
    }
  }

  std::cout << cntPrime <<  " prime numbers found" << std::endl;

  if(printPrime) {
    for(int i = 0; i < size; ++i) {
      if(isPrime[i]) {
	std::cout << i << " ";
      }
    }
  }
  return cntPrime;
}

void testIsPrime(int size)
{
  Array ma = Array(size);
  ma.eratosthenesSieve();
}

void testPrimeStat(void) {

  const int maxSize = 1000;
  int primeOccurrence[maxSize] = {0};

  //Print stat
  for(int i = 0; i < maxSize; ++i) {
    int mark =   primeOccurrence[i]/5;
    for(int j = 0; j < mark; ++j) {
      std::cout << "*";
    }
    std::cout << std::endl;
  }
}

bool isHead(int probability) {
  return (rand() < RAND_MAX / probability);
}

void coinFlipSimulation(int nExp, int  nFlip) {

  int* nHeads = new int[nFlip+1]; //increased by 1 to index the array with the counter
  std::ofstream out("flipSimulation.txt");
  srand(time(NULL));

  for(int j = 0; j <= nFlip; ++j) {
	nHeads[j] = 0;
  }

  for(int i = 0; i < nExp; ++i) {
    int cnt = 0;
    for(int j = 0; j <= nFlip; ++j) {
      if(isHead(6)) {
	cnt++;
      }
    }
    ++nHeads[cnt];
  }
  for(int i = 0; i <= nFlip; ++i) {
    if(nHeads[i] == 0) {
      out << ". \n";
    }
    else {
      for(int j = 0; j < nHeads[i]; j+=10) {
	out << "*";
      }
      out << "\n";
    }
  }
}

std::ostream& operator<<(std::ostream& out, const Array& rhs) {
  for (int i = 0; i<rhs.size;++i) out << rhs.a[i] << " ";
  out << std::endl;
  return out;
}

//recursively find the max element
int Array::max (int idx) {
  if (idx == size-1) return a[idx];
  int x = max (idx+1);
  return (a[idx] > x) ? a[idx] : x;
}
