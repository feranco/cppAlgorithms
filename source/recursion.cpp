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

int getRulerMark (int i) {
  int m = i/2;
  if (m != 0) {
    if (i%2 == 0) cnt++;
    else cnt = 0;
    getRulerMark (m);
  }
  return cnt;
}



