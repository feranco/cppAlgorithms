#include "record.h"
#include <cstring>
#include <cstdlib>
#include <ctime>

//student record implementation
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

//integer vector record implementation
bool IntVector::init = false;

IntVector::IntVector () {
  if (!init) {
    srand(time(0));
    init = true;
  }
  for (int i = 0; i < n; ++i) v[i] = rand() & 100;
}

IntVector::IntVector (const IntVector& rhs) {
  for (int i = 0; i < n; ++i) v[i] = rhs.v[i];
}

IntVector& IntVector::operator= (const IntVector& rhs) {  
  if (this != &rhs) for (int i = 0; i < n; ++i) v[i] = rhs.v[i];
  return *this;
}

bool operator< (const IntVector& lhs, const IntVector& rhs) {
  int i = 0;
  while (lhs.v[i] == rhs.v[i] && i < lhs.n)  ++i;
  return lhs.v[i] < rhs.v[i];
}

std::ostream& operator<<(std::ostream& out, const IntVector& rhs) {
  for (int i = 0; i < rhs.n; ++i) out << rhs.v[i] << " ";
  out << std::endl;
  return out;
}

bool IntVectorPtr::operator< (const IntVectorPtr& rhs) {
  int i = 0;
  while (r->v[i] == rhs.r->v[i] && i < r->n)  ++i;
  return r->v[i] < rhs.r->v[i];
}
