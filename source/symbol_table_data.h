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

  //for data random generation
  static std::random_device rd;//seed
  static std::mt19937 mt;
  static std::uniform_int_distribution<int> dist;
  static std::uniform_int_distribution<int> distc;
  static std::uniform_real_distribution<float> distf;

 public:
  StData (): k(min_key){};
  Key  key () {return k;}
  bool null() {return k == min_key;}
  void rand (void);
  friend std::istream&  operator>> (std::istream& is, StData& rhs);
  friend std::ostream& operator<< (std::ostream& os, StData& rhs);  
};



#endif
