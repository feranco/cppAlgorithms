#include "symbol_table_data.h"

std::random_device StData::rd;
std::mt19937 StData::mt(StData::rd());
std::uniform_int_distribution<int> StData::dist(0, 1000);
std::uniform_int_distribution<int> StData::distc(65, 90);
std::uniform_real_distribution<float> StData::distf(0, 100);

void StData::rand (void) {
  k = dist(mt);
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
