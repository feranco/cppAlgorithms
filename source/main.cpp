#include <iostream>
#include <fstream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include "symbol_table_data.h"
#include "symbol_table_test.h"
#include "unsorted_list_st.h"

int main(int argc, char* argv[])
{

  UnsortedListSt<StData,Key> st;

  testST(st);
  return 0;
}

 
