#ifndef RECORD_H
#define RECORD_H
//interfaces for different records that can be used as Items
//to test sorting algorithms

#include <iostream>
#include <string>

//variable size record
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

typedef Student Record;

#endif
