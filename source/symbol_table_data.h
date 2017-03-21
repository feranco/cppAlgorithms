#ifndef SYMBOL_TABLE_DATA
#define SYMBOL_TABLE_DATA

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <random>

typedef int Key;

static int min_key = -1;

class StData {
  Key   k;
  char  c;
  float f;

  std::random_device seed;
  std::mt19937 mt;
  std::uniform_int_distribution<int> dist;
  std::uniform_int_distribution<int> distc;
  std::uniform_real_distribution<float> distf;

 public:
  StData (): k(min_key){
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> dist(0, 1000);
    std::uniform_int_distribution<int> distc(65, 90);
    std::uniform_real_distribution<int> distf(0, 100);
    std::cout <<  dist(mt) << " ";
  }
  Key  key () {return k;}
  bool null() {return k == min_key;}
  void rand (void);
  friend std::istream&  operator>> (std::istream& is, StData& rhs);
  friend std::ostream& operator<< (std::ostream& os, StData& rhs);
  
};

void StData::rand (void) {
  k = dist(mt);
  std::cout << k << " ";
  c = static_cast<char>(distc(mt));
  f = distf(mt);
}

std::istream&  operator>> (std::istream& is, StData& rhs) {
  is >> rhs.k >> rhs.c >> rhs.f;
  return is;
}

std::ostream& operator<< (std::ostream& os, StData& rhs) {
  os << "k: "<< rhs.k << " c: " << rhs.c << " f: " << rhs.f << std::endl;
  return os;
}

#endif
