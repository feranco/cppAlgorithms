#include "recursion.h"
#include <iostream>
#include <string>
#include <cmath> //pow

const char* expr = "(5 * (((9+8) * (4*6)) + 7))"; //infix string
int idx = 0; //currently evaluated character

int calc (int l, char op, int r) {
  
  switch (op) {
  case '+':
    return l + r;
    break;
    
  case '-':
    return l - r;
    break;

 case '*':
    return l * r;
    break;

 case '/':
    return l / r;
    break;

  default:
    return 0;
  }
}

int infixEval () {
  int token;
  char op = 0;
  int lhs, res;

  while (1) {

    token = expr[idx++];

    if (token == ' ') continue; //skip spaces

    if (token >= '0' && token <= '9') {
      int x = 0;
      --idx; //necessary to manage multiple digit numbers
      //convert string numbers to int 
      while (expr[idx] >= '0' && expr[idx] <= '9') {
	x = 10 * x + expr[idx++] - '0';
      }

      if (op == 0) {
	lhs = x;
      }
      else {
	res = calc (lhs, op, x);
      }
    }
    
    if (token == '(') {
      int x = infixEval();
      if (expr[idx] == 0) return x; //return the final value
      if (op == 0) {
	lhs = x;
      }
      else {
	res = calc(lhs, op, x);
      }
    }

    if (token == '+' || token == '-' || token == '*' || token == '/') {
      op = token;
    }

    if (token == ')') {
      return res;
    } 
  }
  return res;
}

void infixToPostfix (void) {
  char op; //hold the current level operator
  char token;

  while (expr[idx] != 0) {
    
    token = expr[idx++];

    if (token  == ' ') continue; //skip spaces

    if (token >= '0' && token <= '9') {
      std::cout << token << " ";
    }
    else if (token == '+' || token == '*') {
      op = token;
    }
    else if (token == '(') {
      infixToPostfix();
    }
    else if (token == ')') {
      std::cout << op << " ";
      return;
    } 
  }
}


void binaryMatrix (int** bm, int n) {
  
  if (n == 0) return;
  
  int rows = pow (2, n);
  int m = pow (2, n-1);
  for (int i= 0; i < m; ++i) bm[i][n-1] = 0;
  binaryMatrix (bm, n-1);
  for (int i= m; i < rows; ++i) bm[i][n-1] = 1;
  binaryMatrix (&bm[m], n-1);
}

//build a matrix 2^n * n
//with all binary numbers with n digits
void testBinaryMatrix (int n) {

  int rows = pow (2, n);

  //create matrix
  int** bm;
  bm = new int*[rows];
  for (int i = 0; i < rows; ++i) {
    bm[i] = new int[n];
  }

  //fill matrix
  binaryMatrix (bm, n);

  //print matrix
  for (int i = 0; i < rows; ++i) {
    for (int j = n-1; j >=0; --j) {
      std::cout << bm[i][j] << " ";
    }
    std::cout << std::endl;
  }

  //delete matrix
  for (int i = 0; i < n; ++i) {
    delete[] bm[i];
  }
  delete[] bm;
}

int getRulerMark (int i) {
  static int cnt = 0;
  int m = i/2;
  if (m != 0) {
    if (i%2 == 0) cnt++;
    else cnt = 0;
    getRulerMark (m);
  }
  return cnt;
}

//Compute Fibonacci in costant space
int Fibonacci (int n) {
  int a = 0, b = 1, f;
  if (n == 0) return a;
  if (n == 1) return b;
  for (int i = 2; i <= n; ++i) {
    f = b + a;
    a = b;
    b = f;
  }
  return f;
}

int recurrenceCF (int n) {
  int* a = new int[n+1];
  a[0] = a[1] = 0;
  for (int i = 2; i <= n; ++i) {
    a[i] = i/2 + a[(int)floor((float)i/2)] + a[(int)ceil((float)i/2)];
  }
  int r = a[n];
  delete[] a;
  return r;
}

void testRecurrenceCF (void) {
  for (int i = 0; i <=1024; ++i) {
    int r = recurrenceCF (i);
    float s = r - (i*log10(i/2));
    int f = (int)s;
    for (int j = 0; j < f; j+=100){
      std::cout << "*";
    }
    std::cout << std::endl;
  }
  
}

int recurrenceCFTD (int n) {
  static int knownCF[20];
  if (n <= 1) return 0;
  if (knownCF[n] != 0) return knownCF[n];
  knownCF[n] =  n/2 + recurrenceCFTD((int)floor((float)n/2)) + recurrenceCFTD((int)ceil((float)n/2)); 
  return knownCF[n];
}

//knapsack problem definition 
struct Item{
  int size;
  int val;
};

Item items[] = {{9,13},{8,11},{7,10},{4,5},{3,4}};
int knapArray[20] = {0};

//bottom up implementation of the knapsack problem
int knapBU (int n) {

  for (int i = 0; i <= n; ++i) {
    int cap = i;
    int max = 0;
    for (int j = 0; j < 5; ++j) {
      if (items[j].size <= cap) {
	if (items[j].size + knapArray[cap-items[j].size] > max) {
	  max = items[j].val + knapArray[cap-items[j].size];
	}
      }
    }
    knapArray[i] = max;
  }
  return  knapArray[n];
}

//Compute max of array a, splitting a in k parts
//and computing (recursively) the max of each part
int maxK (int a[], int k, int l, int r) {

  if (l == r) return a[l];
  int size = r-l+1; //array size
  int chunk_size = size / k; //std size of chunks
  int chunk_fill = size % k; //to increase size of some chunks
  int begin = l;
  int end = begin + ((chunk_fill-- > 0) ? chunk_size : chunk_size - 1);
  int max = 0;

  for (int i = 0; i < std::min(k,size); ++i) {
    int t = maxK (a, k, begin, end);
    begin = end + 1;
    end = begin + ((chunk_fill-- > 0) ? chunk_size : chunk_size - 1);
    max = std::max(t,max);
  }

  return max;
}
