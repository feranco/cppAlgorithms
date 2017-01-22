#include "record.h"
#include <cstring>

Student::Student (char* n, int g) {
  name = new char[strlen(n)+1];
  strcpy(name,n);
  grade = g;
}

Student::Student (const Student& rhs) {
   name = new char[strlen(rhs.name)+1];
   strcpy(name,(rhs.name));
   grade = rhs.grade;
}

Student& Student::operator=(const Student& rhs) {
  if(&rhs != this) {
    if (name) {
      delete[] name;
    }
    name = new char[strlen(rhs.name)+1];
    strcpy(name,(rhs.name));
    grade = rhs.grade;
  }
  return *this;
}

bool operator<(const Student& lhs, const  Student& rhs) {
  return lhs.grade < rhs.grade;
}

std::ostream& operator<<(std::ostream& out, const Student& rhs) {
  out << rhs.name << " : " << rhs.grade;
  return out;
}

std::istream& operator>>(std::istream& in, Student& rhs) {
    
  in >> rhs.name >> rhs.grade;
  return in;
}
