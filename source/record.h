#ifndef RECORD_H
#define RECORD_H
//interfaces for different records that can be used as Items
//to test sorting algorithms

#include <iostream>
#include <string>

//student record
class Student {
  char* name;
  int grade;
 public:
  Student (){name = new char[30]; grade = 0;}
  Student (char* name, int grade);
  Student (const Student& rhs);
  ~Student(){if (name) delete[] name;};
  Student& operator=(const Student& rhs);
  friend bool operator<(const Student& lhs, const  Student& rhs);
  friend std::ostream& operator<<(std::ostream& out, const Student& rhs);
  friend std::istream& operator>>(std::istream& in, Student& rhs);
};

//n-dimensional integer vectors
class IntVector {
  static const int n = 3;
  static bool init;
  int v[n];
 public:
  IntVector ();
  ~IntVector () {};
  IntVector (const IntVector& rhs);
  IntVector& operator= (const IntVector& rhs);
  friend bool operator< (const IntVector& lhs, const IntVector& rhs);
  friend std::ostream& operator<<(std::ostream& out, const IntVector& rhs);
  friend struct IntVectorPtr;
};

//wrap struct to order by ptr
struct IntVectorPtr {
  IntVector* r;
  IntVectorPtr () {r = 0;}
  //defined as internal member to grant friendship with IntVector
  bool operator< (const IntVectorPtr& rhs);
};

void inPlaceSorting2 (IntVector data[], IntVectorPtr ptr[], int n);

typedef IntVector Record;
typedef IntVectorPtr RecordPtr;
#endif
